#pragma once

#include <stdint.h>
#include <kernel/desc_tables/idt.h>
#include <kernel/desc_tables/int.h>

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, ebx, edx, ecx, eax;
  uint32_t error, int_num;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;


typedef void (*isr_t)(registers_t *);
void isr_handler(registers_t* registers);
void irq_handler(registers_t* registers);
void register_int_handler(uint8_t n, isr_t handler);
