#pragma once
#include <kernel/terminal/terminal.h>
#include <stdint.h>

#define COM1 0x3f8

inline unsigned char inb(uint16_t port)
{
  unsigned char data = 0;
  __asm__ __volatile__ ("inb %%dx, %%al" : "=a" (data) : "d" (port));
  return data;
}

inline void outb(uint16_t port, unsigned char data)
{
  __asm__ __volatile__ ("outb %%al, %%dx" :: "a" (data),"d" (port));
}

void serial_init();
uint32_t serial_check_transmit();
void serial_send_char(char a);
void serial_send_char(char a);
