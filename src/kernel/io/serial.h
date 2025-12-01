#pragma once
#include <stdint.h>

#define COM1 0x3f8


inline unsigned char inb(uint16_t port);
inline void outb(uint16_t port, unsigned char data);
uint32_t serial_check_transmit();
void serial_send_char(char a);
void serial_send_string(char* a);
void serial_init();
