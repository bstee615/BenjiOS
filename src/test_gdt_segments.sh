rm *.o
rm test_gdt_segments
nasm -f elf64 reset_gdt_registers.s -o reset_gdt_registers.o
gcc -o test_gdt_segments test_gdt_segments.c gdt.c reset_gdt_registers.o
./test_gdt_segments
