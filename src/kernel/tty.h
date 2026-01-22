#pragma once

#include <kernel/drivers/vga.h>
#include <kernel/common.h>
#include <kernel/kernel_main.h>

#include <stdint.h>
#include <stddef.h>

extern uint16_t* terminal_buffer;
extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, 
						 size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_scroll(void);
void terminal_delete_last_line(void);
void kwritechar(const char* data, size_t size);
void krwrite(const char* data);
void klog(const char* data);
void kerr(const char* data);
