CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
CLANGFLAGS = -Wall -O2 -ffreestanding -mcpu=cortex-a72+nosimd -fno-common -ffunction-sections -fdata-sections

all: clean kernel8.img

boot.o: boot.S
	clang --target=aarch64-elf $(CLANGFLAGS) -c boot.S -o boot.o

%.o: %.c
	clang --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	ld.lld -m aarch64elf boot.o $(OFILES) -T link.ld -o kernel8.elf -Map kernel8.map
	llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf *.o *.img *.map> /dev/null 2> /dev/null || true

run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio
