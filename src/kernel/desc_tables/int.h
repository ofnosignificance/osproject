#pragma once

#include <stdint.h>
#include <kernel/desc_tables/idt.h>

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, ebx, edx, ecx, eax;
  uint32_t error, int_num;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void isr_handler(registers_t* registers);
