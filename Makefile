NAME := osproject
CXX := i686-elf-g++
CXXFLAGS := -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-exceptions -fno-rtti
AS := nasm
ASFLAGS := -f elf
LDFLAGS := 

SRC_DIR := src
BUILD_DIR := dst
OBJS := $(BUILD_DIR)/kernel_main.cpp.o \
        $(BUILD_DIR)/boot.o

all: $(NAME).bin

$(NAME).bin: $(OBJS)
	$(CXX) -T linker.ld -o $(NAME).bin $(CXXFLAGS) $(OBJS) -lgcc

$(BUILD_DIR)/kernel_main.cpp.o: $(SRC_DIR)/kernel/kernel_main.cpp
	$(CXX) -c $(SRC_DIR)/kernel/kernel_main.cpp $(CXXFLAGS) -o $(BUILD_DIR)/kernel_main.cpp.o

$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $(SRC_DIR)/boot.s -o $(BUILD_DIR)/boot.o

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
	qemu-system-i386 -kernel $(NAME).bin

clean:
	rm -rf $(NAME).bin $(BUILD_DIR)/*
	rm -rf iso


.PHONY: all clean isomake boot