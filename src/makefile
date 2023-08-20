#Genereaza liste de surse folosing wildcard
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

#Converteste tot ce e .c in .o
OBJ = ${C_SOURCES:.c=.o}

all: os.bin

run: all
	../utils/qemu-system-x86_64.exe os.bin

os.bin: kernel/kernel.bin boot/boot_sector.bin
	copy boot\boot_sector.bin/b+kernel\kernel.bin/b os.bin/b

kernel/kernel.bin: kernel/kernel.temp
	objcopy -O binary $< $@

kernel/kernel.temp: kernel/kernel_entry.o ${OBJ}
	ld -o $@ -T ../utils/linkercfg.ld $^ -nostdlib

%.o: %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

%.o: %.asm
	../utils/nasm -f elf $< -o $@

$.bin: %.asm
	../utils/nasm -f bin $< -o $@