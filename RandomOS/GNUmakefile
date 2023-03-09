# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

.PHONY: all
all: ovmf-x64 barebones.iso

.PHONY: all-hdd
all-hdd: ovmf-x64 barebones.hdd

.PHONY: run-uefi
run-uefi:
	qemu-system-x86_64 -M q35 -m 2G -bios firmware/ovmf-x64/OVMF.fd -cdrom barebones.iso -boot d

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-x64 barebones.hdd
	qemu-system-x86_64 -M q35 -m 2G -bios firmware/ovmf-x64/OVMF.fd -hda barebones.hdd

ovmf-x64:
	mkdir -p firmware/ovmf-x64
	cd firmware/ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	cd bootloader && git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	$(MAKE) -C bootloader/limine CC=x86_64-linux-gnu-gcc

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

barebones.iso: limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp kernel/kernel.elf \
		bootloader/limine.cfg bootloader/limine/limine.sys bootloader/limine/limine-cd.bin bootloader/limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o barebones.iso
	limine/limine-deploy barebones.iso
	rm -rf iso_root

barebones.hdd: limine kernel
	rm -f barebones.hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=barebones.hdd
	parted -s barebones.hdd mklabel gpt
	parted -s barebones.hdd mkpart ESP fat32 2048s 100%
	parted -s barebones.hdd set 1 esp on
	limine/limine-deploy barebones.hdd
	sudo losetup -Pf --show barebones.hdd >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	mkdir -p img_mount
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v kernel/kernel.elf limine.cfg limine/limine.sys img_mount/
	sudo cp -v bootloader/limine/BOOTX64.EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`
	rm -rf loopback_dev img_mount

.PHONY: clean
clean:
	rm -rf iso_root barebones.iso barebones.hdd
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf bootloader/limine firmware/ovmf-x64
	$(MAKE) -C kernel distclean
