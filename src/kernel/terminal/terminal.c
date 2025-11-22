#include <kernel/common.h>
#include <kernel/kernel_main.h>
#include <kernel/terminal/terminal.h>



size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void check_space_left(void)
{
	if(terminal_row >= VGA_HEIGHT) {
		for (uint32_t iter = 0; iter < ARRAY_SIZE(terminal_buffer); iter++) {
			terminal_buffer[iter]++;
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{

	switch(c) {
	case '\n':
		terminal_column = 0;
		terminal_row++;
		break;
	default:
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
		break;
	}
}

void kwritechar(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void kwrite(const char* data) 
{
	if (terminal_color != VGA_COLOR_WHITE)
		terminal_setcolor(VGA_COLOR_WHITE);

	kwritechar(data, strlen(data));
}

void kerr(const char* data)
{
	if(terminal_color != VGA_COLOR_RED)
		terminal_setcolor(VGA_COLOR_RED);

	kwritechar(data, strlen(data));
}

void klog(const char* data)
{
	if(terminal_color != VGA_COLOR_GREEN)
		terminal_setcolor(VGA_COLOR_GREEN);

	kwritechar(data, strlen(data));
}