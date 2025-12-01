#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/terminal/terminal.h>
#include <kernel/misc/random_gen.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/kernel_main.h>
#include <kernel/io/serial.h>


void kernel_main(void) 
{	
  serial_init();
  serial_send_string("test");
  while(1);
	terminal_initialize();
  init_gdt();

}
