#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/kernel_main.h>
#include <kernel/terminal/terminal.h>
#include <kernel/misc/random_gen.h>
#include <kernel/desc_tables/gdt.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void kernel_main(void) 
{	
	terminal_initialize();
	gdt_init();
	kerr("hello world\n");
	kwrite("hello world\n");
	kerr("hello world\n");

}