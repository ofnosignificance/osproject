global _disable_int
global _load_gdt
global _flush_gdt 
extern gp

gdtr dw 0
    dq 0

set_gdt:
    mov [gdtr], di
    mov [gdtr + 2], rsi
    lgdt [gdtr]
    ret
    
;; _disable_int:
;;   cli
;;   ret

;; _flush_gdt:
;;   lgdt [gp]
;;   jmp 0x08:.reload_cs

;; .reload_cs:
;;   mov ax, 0x10
;;   mov ds, ax
;;   mov es, ax
;;   mov fs, ax
;;   mov gs, ax
;;   mov ss, ax
;;   ret
