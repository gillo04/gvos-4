;;;             ;;;
;;; Bootloader  ;;;
;;;             ;;;

; What the bootloader does:
; 1) Loads interrupts and shell into memory
; 2) Jumps to long mode (this part was shamelessly stolen and adapted from https://wiki.osdev.org/Entering_Long_Mode_Directly)
; 3) Enables interrupts (partially stolen from the Linux 0.01 kernel)
; 4) Jumps to shell

%define FREE_SPACE 0x9000
[bits 16]
 
; Main entry point where BIOS leaves us.
Main:
    jmp 0x0000:.FlushCS               ; Some BIOS' may load us at 0x0000:0x7C00 while other may load us at 0x07C0:0x0000.
                                      ; Do a far jump to fix this issue, and reload CS to 0x0000.
 
.FlushCS:   
    ; Load enableInterrupts.asm
    ; TODO: loop the interrupt if disk read fails
    xor dx, dx          ; Cilynder and head
    mov cx, 2           ; Starting sector
    mov al, 10          ; Number of sectors to load
    mov ah, 0x02
    mov bx, 0
    mov es, bx
    mov bx, 0x7e00      ; Destination
    int 0x13
 
    ; Set up segment registers.
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    cld
    ; Set up stack so that it starts below Main.
    mov sp, Main
 
    call CheckCPU                     ; Check whether we support Long Mode or not.
    jc .NoLongMode
 
    ; Point edi to a free space bracket.
    mov edi, FREE_SPACE
    jmp SwitchToLongMode
 

[bits 16]
.NoLongMode:
    mov si, NoLongMode
    call Print
    hlt
    jmp $
 
 
%include "enterLongMode.asm"

[bits 16]
NoLongMode db "CPU does not support long mode. For the OS to run you need a 64 bit x86 processor.", 0x0A, 0x0D, 0

; Checks whether CPU supports long mode or not.
; Returns with carry set if CPU doesn't support long mode.
CheckCPU:
    pushfd                            ; Get flags in EAX register.
 
    pop eax
    mov ecx, eax  
    xor eax, 0x200000 
    push eax 
    popfd
 
    pushfd 
    pop eax
    xor eax, ecx
    shr eax, 21 
    and eax, 1                        ; Check whether bit 21 is set or not. If EAX now contains 0, CPUID isn't supported.
    push ecx
    popfd 
 
    test eax, eax
    jz .NoLongMode
 
    mov eax, 0x80000000   
    cpuid                 
 
    cmp eax, 0x80000001               ; Check whether extended function 0x80000001 is available are not.
    jb .NoLongMode                    ; If not, long mode not supported.
 
    mov eax, 0x80000001  
    cpuid                 
    test edx, 1 << 29                 ; Test if the LM-bit, is set or not.
    jz .NoLongMode                    ; If not Long mode not supported.
 
    ret
 
.NoLongMode:
    stc
    ret
 
 
; Prints out a message using the BIOS.
; es:si    Address of ASCIIZ string to print.
Print:
    pushad
.PrintLoop:
    lodsb                             ; Load the value at [@es:@si] in @al.
    test al, al                       ; If AL is the terminator character, stop printing.
    je .PrintDone                  	
    mov ah, 0x0E	
    int 0x10
    jmp .PrintLoop                    ; Loop till the null character not found.
 
.PrintDone:
    popad                             ; Pop all general purpose registers to save them.
    ret

times 510 - ($-$$) db 0
dw 0xaa55

%include "enableInterrupts.asm"
times 512*3 - ($-$$) db 0