#include <stdint.h>
#include <kernel/kernel_main.h>
#include <kernel/desc_tables/gdt.h>

gdt_entry_t gdt[3];
gdt_ptr_t gp;

void gdt_set_gate(uint32_t n, uint32_t base, uint32_t limit,
uint8_t access, uint8_t gran)
{
	gdt[n].base_low = (base & 0xFFFF);
	gdt[n].base_middle = (base >> 16) & 0xFF;
	gdt[n].base_high = (base >> 24) & 0xFF;
	gdt[n].limit_low = (limit & 0xFFFF);
	gdt[n].granularity = ((limit >> 16) & 0x0F);

	gdt[n].granularity |= (gran & 0xF0);
	gdt[n].access = access;
}
void gdt_init()
{
	gp.limit = (sizeof(gdt_entry_t) * 3) - 1;
	gp.base = (uint32_t)&gdt;
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
}