#include <kernel/desc_tables/idt.h>
#include <string.h>

#define IDT_ENTRY_NUM 256

__attribute__((aligned(0x10))) 
idt_entry_t idt_entry[IDT_ENTRY_NUM];
idt_ptr_t ip;

void idt_set_entry(uint8_t i, uint32_t base, uint32_t selector, 
uint8_t type_attributes)
{
	idt_entry[i].offset_low = base & 0xffff;
	idt_entry[i].offset_high = (base >> 16) & 0xffff;
	idt_entry[i].selector = selector;
	idt_entry[i].zero = 0;
	idt_entry[i].type_attributes = type_attributes;
}

void pics_init()
{
  outb(0x20, 0x11);
  outb(0xA0, 0x11);

  outb(0x21, 0x20);
  outb(0xA1, 0x28);

  outb(0x21, 0x04);
  outb(0xA1, 0x02);

  outb(0x21, 0x01);
  outb(0xA1, 0x01);

  outb(0x21, 0x0);
  outb(0xA1, 0x0);
}

void idt_init()
{
	ip.limit = IDT_ENTRY_NUM * sizeof(idt_entry_t);
	ip.ptr = &idt_entry;
  idt_set_entry(0, (uint32_t)isr0, 0x08, 0x8e);
  idt_set_entry(1, (uint32_t)isr1, 0x08, 0x8e);
  idt_set_entry(2, (uint32_t)isr2, 0x08, 0x8e);
  idt_set_entry(3, (uint32_t)isr3, 0x08, 0x8e);
  idt_set_entry(4, (uint32_t)isr4, 0x08, 0x8e);
  idt_set_entry(5, (uint32_t)isr5, 0x08, 0x8e);
  idt_set_entry(6, (uint32_t)isr6, 0x08, 0x8e);
  idt_set_entry(7, (uint32_t)isr7, 0x08, 0x8e);
  idt_set_entry(8, (uint32_t)isr8, 0x08, 0x8e);
  idt_set_entry(9, (uint32_t)isr9, 0x08, 0x8e);
  idt_set_entry(10, (uint32_t)isr10, 0x08, 0x8e);
  idt_set_entry(11, (uint32_t)isr11, 0x08, 0x8e);
  idt_set_entry(12, (uint32_t)isr12, 0x08, 0x8e);
  idt_set_entry(13, (uint32_t)isr13, 0x08, 0x8e);
  idt_set_entry(14, (uint32_t)isr14, 0x08, 0x8e);
  idt_set_entry(15, (uint32_t)isr15, 0x08, 0x8e);
  idt_set_entry(16, (uint32_t)isr16, 0x08, 0x8e);
  idt_set_entry(17, (uint32_t)isr17, 0x08, 0x8e);
  idt_set_entry(18, (uint32_t)isr18, 0x08, 0x8e);
  idt_set_entry(19, (uint32_t)isr19, 0x08, 0x8e);
  idt_set_entry(20, (uint32_t)isr20, 0x08, 0x8e);
  idt_set_entry(21, (uint32_t)isr21, 0x08, 0x8e);
  idt_set_entry(22, (uint32_t)isr22, 0x08, 0x8e);
  idt_set_entry(23, (uint32_t)isr23, 0x08, 0x8e);
  idt_set_entry(24, (uint32_t)isr24, 0x08, 0x8e);
  idt_set_entry(25, (uint32_t)isr25, 0x08, 0x8e);
  idt_set_entry(26, (uint32_t)isr26, 0x08, 0x8e);
  idt_set_entry(27, (uint32_t)isr27, 0x08, 0x8e);
  idt_set_entry(28, (uint32_t)isr28, 0x08, 0x8e);
  idt_set_entry(29, (uint32_t)isr29, 0x08, 0x8e);
  idt_set_entry(30, (uint32_t)isr30, 0x08, 0x8e);
  idt_set_entry(31, (uint32_t)isr31, 0x08, 0x8e);
  
  pics_init();
  idt_set_entry(32, (uint32_t)irq0, 0x08, 0x8e);
  idt_set_entry(33, (uint32_t)irq1, 0x08, 0x8e);
  idt_set_entry(34, (uint32_t)irq2, 0x08, 0x8e);
  idt_set_entry(35, (uint32_t)irq3, 0x08, 0x8e);
  idt_set_entry(36, (uint32_t)irq4, 0x08, 0x8e);
  idt_set_entry(37, (uint32_t)irq5, 0x08, 0x8e);
  idt_set_entry(38, (uint32_t)irq6, 0x08, 0x8e);
  idt_set_entry(39, (uint32_t)irq7, 0x08, 0x8e);
  idt_set_entry(40, (uint32_t)irq8, 0x08, 0x8e);
  idt_set_entry(41, (uint32_t)irq9, 0x08, 0x8e);
  idt_set_entry(42, (uint32_t)irq10, 0x08, 0x8e);
  idt_set_entry(43, (uint32_t)irq11, 0x08, 0x8e);
  idt_set_entry(44, (uint32_t)irq12, 0x08, 0x8e);
  idt_set_entry(45, (uint32_t)irq13, 0x08, 0x8e);
  idt_set_entry(46, (uint32_t)irq14, 0x08, 0x8e);
  idt_set_entry(47, (uint32_t)irq15, 0x08, 0x8e);
  
  _idt_flush();
  klog("IDT: Flushed\n");
}
