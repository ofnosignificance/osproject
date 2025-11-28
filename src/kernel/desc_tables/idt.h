#pragma once

#include <stdint.h>

extern _int_handler();

const char* exception_names = [
	"Divide by zero",
	"Debug",
	"Non-maskable interrrupt",
	"Breakpoint",
	"Into detected overflow",
	"Out of bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Copressor segment overrrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protecton fault"
	"Page fault",
	"Unknown interrupt",
	"Copressor fault",
	"Alignment check",
	"Machine check",
	"SIMD Floating-Point",
];

typedef struct {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attributes;
	uint16_t offset_high;
} idt_entry_t;

typedef struct {
	uint16_t limit;
	void* ptr;
} idt_ptr_t;

void idt_set_entry(uint8_t i, uint32_t base, uint32_t selector, 
uint8_t flags);