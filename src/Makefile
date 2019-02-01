ROOTDIR = ..
OBJ = $(ROOTDIR)/obj
BIN = $(ROOTDIR)/bin

HEADERS = libc kernel
INCLUDE = $(addprefix -I, $(HEADERS))

KERNEL = $(addprefix kernel/, boot descriptor_tables gdt irq sidt terminal kmain pm)
LIBC = $(addprefix libc/, math)

SRC = $(KERNEL) $(LIBC) # Add chunks of source here.
OBJS = $(addsuffix .o, $(SRC))

CC = i686-elf-gcc
FLAGS = -ffreestanding -std=gnu99 -nostdlib -g

IMG = mykernel.elf

default: os

urn:
	echo "They'll do that for you when you're dead, dummy."

run: os
	qemu-system-i386 -s -kernel $(BIN)/$(IMG)

run-test: test
	$(BIN)/test_gdt_segments

run-monitor: os
	qemu-system-i386 -monitor stdio -s -kernel $(BIN)/$(IMG)

clean:
	rm $(OBJ)/*.o 2> /dev/null || true
	rm $(BIN)/*.elf 2> /dev/null || true

os: $(OBJS)
	$(CC) $(FLAGS) -T linker.ld $(patsubst %.o,$(OBJ)/%.o,$(OBJS)) -o $(BIN)/$(IMG) -lgcc

%.o: %.s
	mkdir -p $(dir $(OBJ)/$@)
	nasm -f elf32 $< -o $(OBJ)/$@
%.o: %.c
	mkdir -p $(dir $(OBJ)/$@)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(OBJ)/$@
