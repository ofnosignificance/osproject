#include <kernel/io/serial.h>
#include <kernel/terminal/terminal.h>
#include <stdint.h>

extern inline unsigned char inb(uint16_t port)
{
  unsigned char data = 0;
  __asm__ __volatile__ ("inb %%dx, %%al" : "=a" (data) : "d" (port));
  return data;
}

extern inline void outb(uint16_t port, unsigned char data)
{
  __asm__ __volatile__ ("outb %%al, %%dx" :: "a" (data),"d" (port));
}

void serial_init()
{
  outb(COM1 + 1, 0x00);    
  outb(COM1 + 3, 0x80);
  outb(COM1 + 0, 0x03);
  outb(COM1 + 1, 0x00);
  outb(COM1 + 3, 0x03);
  outb(COM1 + 2, 0xC7);
  outb(COM1 + 4, 0x0B);
  outb(COM1 + 4, 0x1E);
  outb(COM1 + 0, 0xAE);
  
  if(inb(COM1 + 0) != 0xAE) {
    kerr("Faulty serial connection");
  }

  outb(COM1 + 4, 0x0F); 
}

uint32_t serial_check_transmit() 
{
  return inb(COM1 + 5) & 0x20;
}

void serial_send_char(char a) 
{
//  while(serial_check_transmit() == 0);
  outb(COM1, a);
}

void serial_send_string(char* a)
{
  size_t i = 0;
  while(a[i] != '\0') {
    serial_send_char(a[i]);
    i++;
  }
}
