#include <kernel/tty.h>

#include <kernel/drivers/vga.h>
#include <kernel/common.h>
#include <kernel/kernel_main.h>

#include <stdint.h>

uint16_t* terminal_buffer;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(const uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, 
						 size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll(void)
{
    uint16_t* dest = terminal_buffer;
    uint16_t* src = terminal_buffer + VGA_WIDTH;
    
    for (size_t i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
        *dest++ = *src++;
    }
    
    uint16_t blank = vga_entry(' ', terminal_color);
    for (size_t i = 0; i < VGA_WIDTH; i++) {
        *dest++ = blank;
    }

    terminal_row = terminal_row ? terminal_row - 1 : 0;
}
void terminal_delete_last_line(void)
{
    for(size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_putentryat(' ', terminal_color, x, VGA_HEIGHT - 1);
    }
}

void terminal_putchar(const char c)
{
	int32_t line;
	unsigned char uc = c;

	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			for(line = 1; line <= VGA_HEIGHT - 1; line++)
			{
				terminal_scroll();
			}
			terminal_delete_last_line();
			terminal_row = VGA_HEIGHT - 1;
		}
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
	if(terminal_color != VGA_COLOR_GREEN) {
		terminal_setcolor(VGA_COLOR_GREEN);
	}

	kwritechar(data, strlen(data));
}
