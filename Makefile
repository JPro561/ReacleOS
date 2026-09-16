CC = x86_64-elf-gcc
LD = x86_64-elf-ld

CFLAGS = -m64 \
        -mcmodel=kernel \
        -ffreestanding \
        -fno-builtin \
        -fno-stack-protector \
        -fno-pic \
        -mno-red-zone \
        -mno-mmx \
        -mno-sse \
        -mno-sse2 \
        -I. \
        -Wall \
        -Wextra \
        -g


LDFLAGS = -m elf_x86_64 \
        -nostdlib \
        -z max-page-size=0x1000 \
        -T src/linker.ld

all: reacleos.iso

reacleos.iso: src/kernel.c src/vga/vga.c src/linker.ld
	mkdir -p builds/deps iso
	
	$(CC) -c src/kernel.c -o builds/deps/kernel.o $(CFLAGS)
	$(CC) -c src/vga/vga.c -o builds/deps/vga.o $(CFLAGS)
	$(CC) -c src/display/display_manager/dm.c -o builds/deps/dm.o $(CFLAGS)
	$(CC) -c src/display/display/display.c -o builds/deps/display.o $(CFLAGS)
	
	$(LD) $(LDFLAGS) builds/deps/kernel.o builds/deps/vga.o builds/deps/dm.o builds/deps/display.o -o iso/reacleos
	
	xorriso -as mkisofs -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		iso -o builds/reacleos.iso
	
	./limine bios-install builds/reacleos.iso --force
	@echo "\n\n\nTHE SYSTEM WAS BUILT IN '$(PWD)/builds/reacleos.iso'. USE 'make run' TO RUN ReacleOS WITH Qemu"

run:
	qemu-system-x86_64 -cdrom builds/reacleos.iso
	clear

clean:
	rm -rf builds
	rm -f iso/reacleos
