                    mov     esi, 0x7c00+msj
                    mov     ah, 0xE
                    mov     cx, endmsj - msj
writeLoop:
                    lodsb
                    int     0x10
                    dec     cx
                    cmp     cx, 0
                    jne     writeLoop
                    jmp     $

msj db 'Hello from the boot sector!', 10, 13
endmsj:

                    ; PADDING & BIOS MAGIC
         

times 510-($-$$) 	db      0
                    dw      0xaa55