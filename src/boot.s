    ;; boot.s
    bits 32
    extern kernel_main
    extern _kernel_start
    extern _kernel_end
    extern boot_page_directory

    MBALIGN equ (1 << 0)
    MEMINFO equ (1 << 1)
    FLAGS equ (MBALIGN | MEMINFO)
    MAGIC equ 0x1BADB002
    CHECKSUM equ -(MAGIC + FLAGS)

    section .multiboot.data
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

    section .boostrap_stack nobits

    ;; Allocate initial stack
stack_bottom:   
    resb 16384
stack_top:  

    section .bss nobits
    align 4096

boot_page_directory:  
    resb 4096
boot_page_table1:
    resb 4096

    section .multiboot.text
    global _start
_start: 
    mov edi, boot_page_table1 - 0xC0000000
    mov esi, 0
    mov ecx, 1023

    .1:  
    cmp esi, _kernel_start
    jl short .before_kernel
    cmp esi, (_kernel_end - 0xC0000000)
    jge short .past_kernel

    ;; Map physical address as "present, writable"
    mov edx, esi
    or edx, 0x003
    mov [edi], edx

    .before_kernel:
    add esi, 4096
    add edi, 4

    loop .1

    .past_kernel:  
    ;;  Map VGA video memory to 0xC03FF000 as "present, writable"
    mov eax, (0x000B8000 | 0x003)
    mov [dword boot_page_table1 - 0xC0000000 + 1023 * 4], eax

    ;;  page table dir entry 0 (virtually from 0x0 to 0x3fffff)
    ;;  kernel identity mapped at page dir entry 768 (virtually 0xc0000000 to 0xC03fffff)
    mov eax, boot_page_table1 - 0xc0000000 + 0x03
    mov [dword boot_page_directory - 0xc0000000 + 0], eax
    mov eax, boot_page_table1 - 0xc0000000 + 0x003
    mov [dword boot_page_directory - 0xc0000000 + 768 * 4], eax
    
    ;; Set cr3 to the address of the boot_page_directory
    mov ecx, boot_page_directory - 0xc0000000
    mov cr3, ecx

    ;; Enable paging and the write-protect bit
    mov ecx, cr0
    or ecx, 0x80010000
    mov cr0, ecx

    ;; Jump to the higher half with an absolute jump
    lea ecx, [.higher_half]
    add ecx, 0xc0000000
    jmp ecx

    section .text

    .higher_half:
    ;; Unmap the identity mapping now
    mov dword [boot_page_directory + 0], 0
    
    ;; Reload crc3 to force a TLB flush so the changes take effect
    mov ecx, cr3
    mov cr3, ecx

    ;; Set up the stack
    mov esp, stack_top

    ;; Enter the kernel main function
    push ebx
    push eax
    call kernel_main

    cli
    .kernel_hang:  
    hlt
    jmp .kernel_hang
