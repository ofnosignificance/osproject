global _disable_int
global _load_gdt
global _flush_gdt 
extern gp

_disable_int:
    cli
    ret

_flush_gdt:
    lgdt [gp]
    jmp 0x08:_reload_segments

_reload_segments:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
