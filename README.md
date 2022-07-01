# GVOS 4
GVOS 4 is a simple 64 bit operating system written in C++ and Assembly x86.

## Compiling it
To compile GVOS 4, you first need to install a cross-compiler. I setup mine following this [OSDev tutorial](https://wiki.osdev.org/GCC_Cross-Compiler). After this, you can simply run `build.bat` and the project will be compiled down to `gvos4.img` in the root folder. Since I'm working on Windows, in the `build.bat` file, the path for the compiler and the linker are relative to the Windows Subsystem for Linux path I used to install the cross-compiler. `$WSLENV` is an enviroment variable referring to `/usr/local/x86_64elfgcc/bin` in the WSL. You may need to fittle a bit with `build.bat` to get it working for your system. The intermediate files of the compilation get stored in the `bin` folder

## Running it
To run GVOS 4 I use [Virtual Box](https://www.virtualbox.org/), setting the image file generated from the build process as the image of a floppydisk. The system requirements are:
- x86_64 processor
- At least 64MB of ram
- A floppydisk reader

I belive [Bochs](https://bochs.sourceforge.io/) and [Qemu](https://www.qemu.org/) would work aswell, although I have never tried them. I haven't tested it yet on real hardware, but I count on doing that soon.