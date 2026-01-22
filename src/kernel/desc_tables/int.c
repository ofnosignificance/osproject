#include <kernel/desc_tables/int.h>
#include <kernel/desc_tables/idt.h>
typedef void (*isr_t)(registers_t*);

isr_t int_handlers[256];

const char* exception_names[] = {
	"Divide by zero",
	"Debug",
	"Non-maskable interrrupt",
	"Breakpoint",
	"Into detected overflow",
	"Out of bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Copressor segment overrrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protecton fault"
	"Page fault",
	"Unknown interrupt",
	"Copressor fault",
	"Alignment check",
	"Machine check",
	"SIMD Floating-Point",
};


void isr_handler(registers_t* registers)
{
	kerr(exception_names[registers->int_num]);
	kerr("\n");
}

void irq_handler(registers_t* registers)
{
	if(int_handlers[registers->int_num] != 0) {
		isr_t handler = int_handlers[registers->int_num];
		handler(registers);
	}

	outb(0x20, 0x20);
  
	if(registers->int_num < 40) {
		outb(0xa0, 0x20);
	}
}

void register_int_handler(uint8_t n, isr_t handler)
{
	int_handlers[n] = handler; 
}
