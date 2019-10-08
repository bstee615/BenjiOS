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

HEADERS = libc libc/stdlib kernel #test
INCLUDE = $(addprefix -I, $(HEADERS))

KERNEL = $(addprefix kernel/, boot descriptor_tables gdt irq sidt terminal kmain pm io serial idt isr isr_wrapper test_irq irq_handler timer)
LIBC = $(addprefix libc/, math)
# TEST = $(addprefix test/, test_irq)

SRC = $(KERNEL) $(LIBC) #$(TEST) # Add chunks of source here.
OBJ = $(addsuffix .o, $(SRC))

XORRISO = ../tools/xorriso-1.4.6/xorriso/xorriso
CC = ../tools/opt/cross/bin/i686-elf-gcc
QEMU = qemu-system-i386
FLAGS = -ffreestanding -std=gnu99 -nostdlib -g

# echo $(call notice_me, "")
define notice_me
echo "$(RED)$(1)$(NC)"
endef

default: img

urn:
	echo "They'll do that for you when you're dead, dummy."

# Copy os image over to boot dir and make a bootable disk image.
pre-img:
	$(call notice_me, "Creating os image: $(ISOPATH).")
img: os pre-img
	cp $(BINDIR)/$(OS).bin $(IMGPATH)
	if rm $(ISOPATH) 2> /dev/null; then $(call notice_me, "grub-mkrescue: removed previous image: $(OS).iso."); fi
	grub-mkrescue -o $(ISOPATH) --xorriso=$(XORRISO) $(ISODIR)

qemu: img
	$(QEMU) -serial file:qemu_serial.log -cdrom $(ISOPATH)

qemu-d: img
	objcopy --only-keep-debug $(IMGPATH) $(IMGDIR)/$(OS).sym
	$(QEMU) -s -S -serial file:qemu_serial.log $(ISOPATH)

qemu-monitor: img
	$(QEMU) -monitor stdio -serial file:qemu_serial.log $(ISOPATH)

clean:
	rm -r $(ISODIR)/boot/*.bin 2> /dev/null || true
	rm -r $(OBJDIR)/*.o 2> /dev/null || true
	rm -r $(OBJDIR)/kernel/*.o 2> /dev/null || true
	rm -r $(OBJDIR)/libc/*.o 2> /dev/null || true
	rm -r $(BINDIR)/*.bin 2> /dev/null || true
	rm -r $(BINDIR)/*.iso 2> /dev/null || true
	rm -r $(ISODIR)/*.bin 2> /dev/null || true
	rm -r $(ISODIR)/*.iso 2> /dev/null || true

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

%.o: %.s
	nasm -f elf32 $< -o $(OBJDIR)/$@
%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(OBJDIR)/$@
