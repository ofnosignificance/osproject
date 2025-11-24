#include <stdint.h>
#include <kernel/kernel_main.h>
#include <kernel/desc_tables/gdt.h>
#include <kernel/terminal/terminal.h>

#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS     0x09
#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00
#define GDT_FLAG_RING3   0x60
#define GDT_FLAG_PRESENT 0x80
#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400

static gdt_entry_t gdt[5];
static gdt_ptr_t gp;

void gdt_set_entry(int32_t i, uint32_t base, uint32_t limit, int32_t flags)
{
  gdt[i].limit_low = limit & 0xffffLL;
  gdt[i].base_low |= (base & 0xffffffLL) << 16;
  gdt[i].base_middle |= (flags & 0xffLL) << 40;
  gdt[i].access |= ((limit >> 16) & 0xfLL) << 48;
  gdt[i].granularity |= ((flags >> 8 )& 0xffLL) << 52;
  gdt[i].base_high |= ((base >> 24) & 0xffLL) << 56;
}

void init_gdt(void)
{
  _disable_int();
  gp.ptr = &gdt;
  gp.limit = sizeof(gdt[5]) - 1;
  gdt_set_entry(0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
    GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
  gdt_set_entry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
    GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
  gdt_set_entry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
    GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
  gdt_set_entry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
    GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
  klog("The GDT is loaded.\n");
}
