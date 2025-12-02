#include <stdint.h>
#include <kernel/kernel_main.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/terminal/terminal.h>
#include <kernel/io/serial.h>

#define GDT_ENTRY_NUM 3

gdt_entry_t gdt[GDT_ENTRY_NUM];
gdt_ptr_t gp;

void gdt_set_entry(int32_t i, uint32_t base, uint32_t limit, 
uint32_t access, uint32_t granularity)
{
  gdt[i].limit_low = limit & 0xffff;
  gdt[i].base_low = (base >> 16) & 0xff;
  gdt[i].base_middle = (base >> 16) & 0xff;
  gdt[i].base_high = (base >> 24) & 0x0f;
  gdt[i].access = access;
  gdt[i].granularity = ((limit >> 16) & 0x0f);
  gdt[i].granularity = granularity & 0xf0;
}

void init_gdt(void)
{
  _disable_int();
  gp.ptr = &gdt;
  gp.limit = sizeof(gdt);
  gp.ptr = &gdt;
  gdt_set_entry(0, 0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  klog("GDT: Entries were written\n");
  _flush_gdt();
  klog("GDT: Flushed\n");
}
