incbin "gvos4.bin"
times 512*10 - ($-$$) db 0
db "Hello world", 0
times 512*18 - ($-$$) db 0