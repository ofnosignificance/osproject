#include <stdint.h>
#include <kernel/kernel_main.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/terminal/terminal.h>
#include <kernel/io/serial.h>

#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS     0x09
#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00
#define GDT_FLAG_RING3   0x60
#define GDT_FLAG_PRESENT 0x80
#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400

gdt_entry_t gdt[5];
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
  gp.limit = sizeof(gdt[5]) - 1;
  gp.ptr = &gdt;
  gdt_set_entry(0, 0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  klog("GDT: Entries were written\n");
  _flush_gdt();
  klog("GDT: Flushed\n");
}
