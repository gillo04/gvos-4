extern PrintString
extern ScanString

Int_20:
    cmp ah, 0x00
    je TeletypeOut
    cmp ah, 0x01
    je PrintString_gate
    cmp ah, 0x02
    je GetScanCode
    cmp ah, 0x03
    je SetCursorPosition
    cmp ah, 0x04
    je GetCursorPosition
    cmp ah, 0x05
    je GetScancodePointer
    cmp ah, 0x06
    je ScanString_gate
    cmp ah, 0x07
    je setColor
    iretq

TeletypeOut:
    push rax
    push dx
    
    ; call GetCursorPosition
    mov ah, 0x04
    int 0x20

    xor eax, eax
    mov ax, 2
    mul bx
    add eax, 0xB8000
    mov ecx, eax

    pop dx
    pop rax
    mov [ecx], al
    mov al, [textColor]
    mov [ecx+1], al

    inc bx
    ; call SetCursorPosition
    mov ah, 0x03
    int 0x20

    iretq

PrintString_gate:
    mov rax, 0
    call PrintString
    iretq

GetScanCode:
    mov dx, 0x64
    in al, dx
    and al, 1
    cmp al, 0
    je GetScanCode
    
    mov dx, 0x60
    in al, dx

    iretq

SetCursorPosition:
    push ax
    push dx
    
    mov al, 0x0f
    mov dx, 0x3d4
    out dx, al

    mov al, bl
    mov dx, 0x3d5
    out dx, al
    
    mov al, 0x0e
    mov dx, 0x3d4
    out dx, al

    mov al, bh
    mov dx, 0x3d5
    out dx, al

    pop dx
    pop ax
    iretq

GetCursorPosition:
    push ax
    push dx
    
    mov al, 0x0f
    mov dx, 0x3d4
    out dx, al

    mov dx, 0x3d5
    in al, dx
    mov bl, al
    
    mov al, 0x0e
    mov dx, 0x3d4
    out dx, al

    mov dx, 0x3d5
    in al, dx
    mov bh, al

    pop dx
    pop ax
    iretq

GetScancodePointer:
    mov rdi, ScanCodeSet1
    iretq

ScanString_gate:
    mov rax, 0
    call ScanString
    iretq

setColor:
    mov [textColor], di
    iretq
textColor db 0x07