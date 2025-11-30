#pragma once
#include <stdint.h>

#define COM1 0x3f8


inline unsigned char inb(uint16_t port);
inline void outb(uint16_t port, unsigned char data);

void serial_init();
