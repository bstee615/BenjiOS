ROOTDIR = ..
OBJDIR = $(ROOTDIR)/obj

BINDIR = $(ROOTDIR)/bin
ISODIR = $(ROOTDIR)/boot
IMGDIR = $(ISODIR)/boot

OS = benjios
ISOPATH = $(ISODIR)/$(OS).iso
IMGPATH = $(IMGDIR)/$(OS).bin

RED = \033[0;31m
NC = \033[0m

IMG = $(OS).bin

HEADERS = kernel libc libc/stdlib descriptor_tables io #test
INCLUDE = $(addprefix -I, $(HEADERS))

KERNEL = $(addprefix kernel/, boot main)
LIBC = $(addprefix libc/, bio)
DT = $(addprefix descriptor_tables/, dt gdt gdt_flush idt idt_flush isr_wrapper isr_handlers isr timer)
IO = $(addprefix io/, monitor)

SRC = $(KERNEL) $(LIBC) $(DT) $(IO)
OBJ = $(addsuffix .o, $(SRC))

XORRISO = ../tools/xorriso-1.4.6/xorriso/xorriso
CC = ../tools/opt/cross/bin/i686-elf-gcc
FLAGS = -Wall -Werror -ffreestanding -std=gnu99 -nostdlib -g

# echo $(call notice_me, "")
define notice_me
echo "$(RED)$(1)$(NC)"
endef

default: os

urn:
	echo "They'll do that for you when you're dead, dummy."

# Copy os image over to boot dir and make a bootable disk image.
pre-img:
	$(call notice_me, "Creating os image: $(ISOPATH).")
img: os pre-img
	cp $(BINDIR)/$(OS).bin $(IMGPATH)
	if rm $(ISOPATH) 2> /dev/null; then $(call notice_me, "grub-mkrescue: removed previous image: $(OS).iso."); fi
	grub-mkrescue -o $(ISOPATH) --xorriso=$(XORRISO) $(ISODIR)

# Delete all generated files.
clean:
	rm -r $(ISODIR)/**/*.bin 2> /dev/null || true
	rm -r $(ISODIR)/**/*.sym 2> /dev/null || true
	rm -r $(ISODIR)/**/*.iso 2> /dev/null || true
	rm -r $(ISODIR)/*.iso 2> /dev/null || true

	rm -r $(BINDIR)/**/*.bin 2> /dev/null || true

	echo $(HEADERS) | tr " " "\n" | while read -r dirname; do rm -r $(OBJDIR)/$$dirname; done

# Create or check existence of directories for object files.
objdirs:
	echo $(HEADERS) | tr " " "\n" | while read -r dirname; do mkdir -p $(OBJDIR)/$$dirname; done

pre-all:
	$(call notice_me, "Compiling all source files into: $(OBJDIR).")
all: pre-all objdirs $(OBJ)

# Make os image and place it in BIN dir.
pre-os:
	$(call notice_me, "Linking all object files into: $(BINDIR)/$(IMG)")
os: all pre-os
	$(CC) $(FLAGS) -T linker.ld $(patsubst %.o,$(OBJDIR)/%.o,$(OBJ)) -o $(BINDIR)/$(IMG) -lgcc

# Pattern matching for ASM/C files.
%.o: %.s
	nasm -f elf32 $< -o $(OBJDIR)/$@
%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(OBJDIR)/$@

QEMU = qemu-system-i386

qemu: img
	$(QEMU) -serial file:qemu_serial.log -cdrom $(ISOPATH)

qemu-d: img
	objcopy --only-keep-debug $(IMGPATH) $(IMGDIR)/$(OS).sym
	$(QEMU) -s -S -serial file:qemu_serial.log $(ISOPATH)

qemu-monitor: img
	$(QEMU) -monitor stdio -serial file:qemu_serial.log $(ISOPATH)
