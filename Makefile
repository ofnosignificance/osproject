NAME := kotorios
CC := x86_64-elf-gcc
CCFLAGS := -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-exceptions -isystem src -I src/libc/include
AS := nasm
ASFLAGS := -f elf64
LDFLAGS := -T linker.ld

SRC_DIR := src
BUILD_DIR := dst
OBJS := $(BUILD_DIR)/kernel_main.c.o \
	$(BUILD_DIR)/serial.c.o \
	$(BUILD_DIR)/random_gen.c.o \
	$(BUILD_DIR)/boot.s.o \
	$(BUILD_DIR)/gdt_helper.s.o \
	$(BUILD_DIR)/gdt.c.o \
	$(BUILD_DIR)/idt.c.o \
	$(BUILD_DIR)/int.c.o \
	$(BUILD_DIR)/int_helper.s.o \
	$(BUILD_DIR)/common.c.o \
	$(BUILD_DIR)/tty.c.o \
	$(BUILD_DIR)/memset.c.o
#	$(BUILD_DIR)/keyboard.c.o 

all: $(BUILD_DIR) $(NAME).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(NAME).bin: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/boot.s.o: $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $< -o $@ 

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/desc_tables/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.s.o: $(SRC_DIR)/kernel/desc_tables/%.s
	$(AS) $(ASFLAGS) $< -o $@ 

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/misc/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/libc/string/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.s.o: $(SRC_DIR)/kernel/%.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/io/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/drivers/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

geniso:
	mkdir -p iso/boot/grub/
	cp $(NAME).bin iso/boot/$(NAME).bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue --output=kotorios.iso iso
	rm -rf iso

runiso:
	qemu-system-x86_64 -cdrom $(NAME).iso

clean:
	rm -rf $(NAME).bin $(BUILD_DIR)/*
	rm -rf iso
	rm -f $(NAME).iso 


.PHONY: all clean geniso boot
