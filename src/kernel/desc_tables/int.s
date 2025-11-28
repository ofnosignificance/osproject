;; interrupts

extern klog
global _int_handler
_int_handler:
	cld
	reti
