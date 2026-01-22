#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/misc/random_gen.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/desc_tables/idt.h>
#include <kernel/kernel_main.h>
#include <kernel/io/serial.h>

void kernel_main(void) 
{	
	terminal_initialize();
	serial_init();
	gdt_init();
	idt_init();
	__asm__ volatile("sti");
	__asm__ volatile("int $1");
}
