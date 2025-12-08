#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/terminal/terminal.h>
#include <kernel/misc/random_gen.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/desc_tables/idt.h>
#include <kernel/kernel_main.h>
#include <kernel/io/serial.h>


void kernel_main(void) 
{	
	terminal_initialize();
  init_gdt();
  idt_init();
}
