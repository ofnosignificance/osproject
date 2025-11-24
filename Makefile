NAME := osproject
CXX := i686-elf-gcc
CXXFLAGS := -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-exceptions -isystem src -I src/libc/include
AS := nasm
ASFLAGS := -f elf
LDFLAGS := 

SRC_DIR := src
BUILD_DIR := dst
OBJS := $(BUILD_DIR)/kernel_main.c.o \
        $(BUILD_DIR)/random_gen.c.o \
        $(BUILD_DIR)/boot.s.o \
        $(BUILD_DIR)/gdt_helper.s.o \
        $(BUILD_DIR)/gdt.c.o \
        $(BUILD_DIR)/idt.c.o \
        $(BUILD_DIR)/idt_helper.s.o \
        $(BUILD_DIR)/common.c.o \
        $(BUILD_DIR)/terminal.c.o \
        $(BUILD_DIR)/memset.c.o

all: $(BUILD_DIR) $(NAME).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(NAME).bin: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/boot.s.o: $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $< -o $@ 

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/desc_tables/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.s.o: $(SRC_DIR)/kernel/desc_tables/%.s
	$(AS) $(ASFLAGS) $< -o $@ 

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/kernel/misc/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/libc/string/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.s.o: $(SRC_DIR)/kernel/%.s
	$(AS) $(ASFLAGS) -o $@ $<

isomake:
	mkdir -p iso/boot/grub/
	cp $(NAME).bin iso/boot/$(NAME)
	echo 'menuentry "$(NAME)" {' >> iso/boot/grub.cfg
	echo '		multiboot /boot/$(NAME).bin"' >> iso/boot/grub.cfg
	echo '		boot' >> iso/boot/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg

	grub-mkrescue --output=$(NAME).iso iso

runiso:
	qemu-system-i386 -cdrom $(NAME).iso

runkernel:
	qemu-system-i386 -kernel $(NAME).bin

clean:
	rm -rf $(NAME).bin $(BUILD_DIR)/*
	rm -rf iso
	rm -f $(NAME).iso 


.PHONY: all clean isomake boot
