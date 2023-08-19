all: kernel/kernel.bin boot/boot_sector.bin

run: all
	../utils/qemu-system-x86_64.exe os.bin

kernel/kernel.bin: kernel/kernel.temp
	objcopy -O binary $< $@

kernel/kernel.temp: kernel/kernel_entry.o kernel/kernel.o
	ld -o $@ -T ../utils/linkercfg.ld $^ -nostdlib

kernel/kernel.o: kernel/kernel.c
	gcc -ffreestanding -c $< -o $@

kernel/kernel_entry.o : kernel/kernel_entry.asm
	../utils/nasm -f elf $< -o $@

boot/boot_sector.bin: boot/boot.asm
	../utils/nasm -f bin $< -o $@