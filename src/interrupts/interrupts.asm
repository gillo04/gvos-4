[bits 64]

;;; --------------------------------------------------
;;;                  INTERRUPT LIST
;;; --------------------------------------------------

; 0xa0: I/O
;       0x00: print character                               [AL: character, BL: color, CX: how many times to print]
;       0x01: print string                                  [RDI: string address]
;       0x02: get scan code                                 (AL: scan code)
;       0x03: set cursor position                           [BX: position]
;       0x04: get cursor position                           (BX: position)
;       0x05: get pointer to scan code set                  (RDI: pointer)
;       0x06: scan string                                   [RDI: output address, RSI: output size]

[global Int_20]
%include "int20.asm"
%include "keyboardConfigs.asm"

times 512*2 - ($-$$) db 0