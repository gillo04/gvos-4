extern PrintString

Int_20:
    cmp ah, 0x0e
    je TeletypeOut
    cmp ah, 0x01
    je PrintString_gate
    iretq

TeletypeOut:
    push rax
    push dx
    
    call GetCursorPosition
    xor eax, eax
    mov ax, 2
    mul bx
    add eax, 0xB8000
    mov ecx, eax

    pop dx
    pop rax
    mov [ecx], al

    inc bx
    call SetCursorPosition

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
    ret

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
    ret

PrintString_gate:
    mov rax, 0
    call PrintString
    jmp $
    iretq