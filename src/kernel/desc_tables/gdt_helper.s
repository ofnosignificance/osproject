global _disable_int
global _load_gdt
extern gp

_disable_int:
	cli
  ret

_load_gdt:
  lgdt [gp]
  ret
