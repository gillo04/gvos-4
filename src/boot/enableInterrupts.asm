[bits 64]
EnableInterrupts:
    ; Finish setting up the IDT with values from linking time
    and word[idt_20.l],  0xffff

    shr word[idt_20.h],  16
    and word[idt_20.h],  0xffff

    ; Load the IDT
    lidt [idt_descr]

    mov al, 0x11                ; initialization sequence
    out 0x20, al                ; send it to 8259A-1
    dw 0x00eb, 0x00eb           ; jmp $+2, jmp $+2
    out 0xA0, al                ; and to 8259A-2
    dw 0x00eb, 0x00eb
    mov al, 0x20                ; start of hardware int's (0x20)
    out 0x21, al
    dw 0x00eb, 0x00eb
    mov al, 0x28                ; start of hardware int's 2 (0x28)
    out 0xA1, al
    dw 0x00eb, 0x00eb
    mov al, 0x04                ; 8259-1 is master
    out 0x21, al
    dw 0x00eb, 0x00eb
    mov al, 0x02                ; 8259-2 is slave
    out 0xA1, al
    dw 0x00eb, 0x00eb
    mov al, 0x01                ; 8086 mode for both
    out 0x21, al
    dw 0x00eb, 0x00eb
    out 0xA1, al
    dw 0x00eb, 0x00eb
    mov al, 0xFF                ; mask off all interrupts for now
    out 0x21, al
    dw 0x00eb, 0x00eb
    out 0xA1, al

    sti

    ; Entering the shell
    extern shell
    call shell

    jmp $

idt_descr:
    dw idt_end - idt_base
    dq idt_base

idt_base:
    times 16*0x20 db 0

extern Int_20
idt_20:
    .l  dw (Int_20-$$+0x7c00)                   ; base low
        dw CODE_SEG                             ; alignment
        db 0                                    ; zero
        db 10001110b                            ; flags
    .h  dw (Int_20-$$+0x7c00)                   ; base high
        dd 0                                    ; base higher
        dd 0                                    ; zero

idt_end: