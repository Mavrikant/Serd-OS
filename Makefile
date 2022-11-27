CFILES = $(wildcard *.c)
SFILES = $(wildcard *.S)
OFILES = $(CFILES:.c=.o) $(SFILES:.S=.o) 
CLANGFLAGS = -Wall -O0 -ffreestanding -mcpu=cortex-a72+nosimd -fno-common -ffunction-sections -fdata-sections

all: clean kernel8.img

run: clean kernel8.img qemu

%.o: %.S
	clang --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

%.o: %.c
	clang --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

kernel8.img: $(OFILES)
	ld.lld -m aarch64elf $(OFILES) -T link.ld -o kernel8.elf -Map kernel8.map
	llvm-objcopy -O binary kernel8.elf kernel8.img
	llvm-objdump -d kernel8.elf  >> kernel8.dump

clean:
	/bin/rm kernel8.elf *.o *.img *.map> /dev/null 2> /dev/null || true

qemu:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio

debug:
	qemu-system-aarch64 -S -M raspi3b -kernel kernel8.img -serial stdio
