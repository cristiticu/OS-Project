printFromAdress:                            ;printFromAdress: subrutina ia adresa stocata 
    push    ax                              ;in bx si afiseara string-ul null-terminat pe ecran
    push    bx
.loop:
    mov     ah, 0xe
    mov     al, byte [bx]
    cmp     al, byte 0
    je      .done
    int     0x10
    inc     bx
    jmp     .loop
.done:
    pop     bx
    pop     ax
    ret

    
    
convertHexToString:                          ;convertHexToString: subrutina ia numarul din bx
    push    ax                               ;si il stocheaza in memorie la adresa data de
    push    bx                               ;convertedHex. (nr pe 16 biti). cx, di, ax, bx
    push    cx
    push    di
    mov     cx, 4                            
    mov     di, convertedHex + 3
.loop:
    mov     al, 0x0f
    and     al, bl
    cmp     al, 10
    jl      .isNumber
    add     al, 39
.isNumber:
    add     al, '0'
    mov     byte [di], al
    shr     bx, 4
    dec     di
    dec     cx
    jnz     .loop
.done:
    pop     di
    pop     cx
    pop     bx
    pop     ax
    ret
    
    
    
printHexNumber:                                             ;Wrapper pentru a afisa pe ecran un numar hexa retinut in registrul bx
    push    bx
    call    convertHexToString                              ;Se calculeaza numarul si se retine in adresa globala
    mov     bx, convertedHex
    call    printFromAdress                                 ;Afisam string-ul de la adresa globala
    pop     bx
    ret