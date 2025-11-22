NAME := osproject
CXX := i686-elf-gcc
CXXFLAGS := -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-exceptions -isystem src
AS := nasm
ASFLAGS := -f elf
LDFLAGS := 

SRC_DIR := src
BUILD_DIR := dst
OBJS := $(BUILD_DIR)/kernel_main.c.o \
		$(BUILD_DIR)/random_gen.c.o \
        $(BUILD_DIR)/boot.o \
		$(BUILD_DIR)/gdt_helper.s.o \
 	    $(BUILD_DIR)/gdt.c.o \
 	    $(BUILD_DIR)/idt.c.o \
 	    $(BUILD_DIR)/common.c.o \
 	    $(BUILD_DIR)/terminal.c.o 

all: $(NAME).bin

$(NAME).bin: $(OBJS)
	$(CXX) -T linker.ld -o $(NAME).bin $(CXXFLAGS) $(OBJS) -lgcc

$(BUILD_DIR)/kernel_main.c.o: $(SRC_DIR)/kernel/kernel_main.c $(SRC_DIR)/kernel/kernel_main.h
	$(CXX) -c $(SRC_DIR)/kernel/kernel_main.c $(CXXFLAGS) -o $(BUILD_DIR)/kernel_main.c.o

$(BUILD_DIR)/random_gen.c.o: $(SRC_DIR)/kernel/misc/random_gen.c $(SRC_DIR)/kernel/misc/random_gen.h
	$(CXX) -c $(SRC_DIR)/kernel/misc/random_gen.c $(CXXFLAGS) -o $(BUILD_DIR)/random_gen.c.o

$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $(SRC_DIR)/boot.s -o $(BUILD_DIR)/boot.o

$(BUILD_DIR)/gdt_helper.s.o: $(SRC_DIR)/kernel/desc_tables/gdt_helper.s
	$(AS) $(ASFLAGS) $(SRC_DIR)/kernel/desc_tables/gdt_helper.s -o $(BUILD_DIR)/gdt_helper.s.o

$(BUILD_DIR)/gdt.c.o: $(SRC_DIR)/kernel/desc_tables/gdt.c $(SRC_DIR)/kernel/desc_tables/gdt.h
	$(CXX) -c $(SRC_DIR)/kernel/desc_tables/gdt.c $(CXXFLAGS) -o $(BUILD_DIR)/gdt.c.o

$(BUILD_DIR)/common.c.o: $(SRC_DIR)/kernel/common.c $(SRC_DIR)/kernel/common.h
	$(CXX) -c $(SRC_DIR)/kernel/common.c $(CXXFLAGS) -o $(BUILD_DIR)/common.c.o

$(BUILD_DIR)/idt.c.o: $(SRC_DIR)/kernel/desc_tables/idt.c $(SRC_DIR)/kernel/desc_tables/idt.h
	$(CXX) -c $(SRC_DIR)/kernel/desc_tables/idt.c $(CXXFLAGS) -o $(BUILD_DIR)/idt.c.o

$(BUILD_DIR)/terminal.c.o: $(SRC_DIR)/kernel/terminal/terminal.c $(SRC_DIR)/kernel/terminal/terminal.h
	$(CXX) -c $(SRC_DIR)/kernel/terminal/terminal.c $(CXXFLAGS) -o $(BUILD_DIR)/terminal.c.o

isomake:
	mkdir -p iso/boot/grub/
	cp $(NAME).bin iso/boot/$(NAME)
	echo 'menuentry "$(NAME)" {' >> iso/boot/grub.cfg
	echo '		multiboot /boot/$(NAME).bin"' >> iso/boot/grub.cfg
	echo '		boot' >> iso/boot/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg

	grub-mkrescue --output=$(NAME).iso iso

runiso:
	qemu-system-i386 \
		-enable-kvm \
		-cdrom $(NAME).iso

runkernel:
	qemu-system-i386 \
	-enable-kvm \
	-kernel $(NAME).bin

clean:
	rm -rf $(NAME).bin $(BUILD_DIR)/*
	rm -rf iso
	rm -f $(NAME).iso 


.PHONY: all clean isomake boot
