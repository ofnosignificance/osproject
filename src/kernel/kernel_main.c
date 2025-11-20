#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/terminal/terminal.h>
#include <kernel/misc/random_gen.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/kernel_main.h>



void kernel_main(void) 
{	
	terminal_initialize();
	gdt_init();
	kerr("hello world\n");
	kwrite("hello world\n");
	kerr("hello world\n");
}