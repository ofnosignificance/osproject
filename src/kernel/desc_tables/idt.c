#include <kernel/desc_tables/idt.h>
#include <string.h>
__attribute__((aligned(0x10))) 
static idt_entry_t idt_entry[256];
static idt_ptr_t idt_ptr;

void idt_set_entry(uint8_t i, uint32_t base, uint32_t selector, 
uint8_t type_attributes)
{
	idt_entry[i].offset_low = (base & 0xffff);
	idt_entry[i].offset_high = (base >> 16) & 0xffff;
	idt_entry[i].selector = selector;
	idt_entry[i].zero = 0;
	idt_entry[i].type_attributes = type_attributes;
}

void init_idt()
{
	idt_ptr.limit = (sizeof(idt_entry_t) * 256) -1;
	idt_ptr.ptr = &idt_entry;
	memset(&idt_entry, 0, sizeof(idt_entry) * 256);

}
