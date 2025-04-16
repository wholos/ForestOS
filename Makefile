C=gcc
ASM=nasm
LD=ld

CFLAGS=-m32 -ffreestanding -nostdlib -Wall -Wextra -c
ASMFLAGS=-f elf32
LDFLAGS=-m elf_i386 -T linker.ld -nostdlib

KERNEL=kernel.bin

all: $(KERNEL)

$(KERNEL): kernel.o kernel_asm.o
	@$(LD) $(LDFLAGS) -o $@ $^

kernel.o: kernel.c
	@$(C) $(CFLAGS)  $< -o $@

kernel_asm.o: kernel.asm
	@$(ASM) $(ASMFLAGS) $< -o $@

clean:
	@rm -f *.o $(KERNEL)

run: all
	@qemu-system-x86_64 -kernel kernel.bin
