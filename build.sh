#!/bin/bash
nasm -f elf32 loader.s
ld -T link.ld -melf_i386 loader.o -o kernel.elf
cp -rf kernel.elf iso/boot/
rm ./kernel.elf
rm ./loader.o
grub-mkrescue -o os.iso iso
