[bits 64]

;;; --------------------------------------------------
;;;                  INTERRUPT LIST
;;; --------------------------------------------------

; ? 0xa0: I/O
;       0x00: print character                               [AL: character, BL: color, CX: how many times to print]
;       0x01: print string                                  [RDI: string address]
;       0x02: get scan code                                 (AL: scan code)
;       0x03: set cursor position                           [BX: position]
;       0x04: get cursor position                           (BX: position)
;       0x05: get pointer to scan code set                  (RDI: pointer)
;       0x06: scan string                                   [RDI: output address, RSI: output size]
; ? 0xa1: GDT functions
; ? 0xa2: Heap
;       0x00: malloc
;       0x01: memfree
;       0x02: realloc
; ? 0xa3: Disk
;       0x00: read disk (CHS)
;       0x01: write disk (CHS)
;       0x03: read disk (LBA)
;       0x04: write disk (LBA)
; ? 0xa4: File system
;       0x00: load file
;       0x01: write file
;       0x02: create file
;       0x03: delete file

[global Int_20]
[global CapsLock]
[global Shift]
%include "int20.asm"
%include "keyboardConfigs.asm"
CapsLock db 0
Shift db 0

times 512*2 - ($-$$) db 0