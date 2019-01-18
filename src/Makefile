ROOTDIR = ..
OBJ = $(ROOTDIR)/obj
BIN = $(ROOTDIR)/bin
SRC = kernel.o boot.o gdt.o flush_gdt.o store_gdt_ptr.o sidt.o io.o
# TEST = test-test_gdt_segments.o $(patsubst %.o,test-%.o,$(GDT))

CC = i686-elf-gcc
FLAGS = -ffreestanding -std=gnu99 -c

IMG = mykernel.elf

# test: $(TEST)
# 	gcc $(patsubst %.o,$(OBJ)/%.o,$(TEST)) -o $(BIN)/$(IMG) -lgcc

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
	rm $(OBJ)/*.o
	rm $(BIN)/*.elf

os: $(SRC)
	i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld $(patsubst %.o,$(OBJ)/%.o,$(SRC)) -o $(BIN)/$(IMG) -lgcc

# test-%.o: %.s
# 	nasm $< -o $(OBJ)/test-$@
# test-%.o: %.c
# 	gcc $< -o $(OBJ)/test-$@

%.o: %.s
	nasm -f elf32 $< -o $(OBJ)/$@
%.o: %.c
	$(CC) $(FLAGS) $< -o $(OBJ)/$@
