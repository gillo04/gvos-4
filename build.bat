nasm -f elf64 -I ./src/boot ./src/boot/boot.asm -o ./bin/boot.o
nasm -f elf64 -I ./src/interrupts ./src/interrupts/interrupts.asm -o ./bin/interrupts.o
wsl $WSLENV/x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "./src/interrupts/printString.cpp" -o "./bin/printString.o"
wsl $WSLENV/x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "./src/shell.cpp" -o "./bin/shell.o"
wsl $WSLENV/x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "./src/lib/stdio.cpp" -o "./bin/stdio.o"

wsl $WSLENV/x86_64-elf-ld --oformat binary -o ./bin/gvos4.bin -Ttext 0x7c00 ./bin/boot.o ./bin/interrupts.o ./bin/printString.o ./bin/shell.o ./bin/stdio.o

nasm -f bin -I ./bin ./src/zeroFill.asm -o ./gvos4.img