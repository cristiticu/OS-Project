org     0x7c00
bits    16


                    jmp short   BIOSEntryPoint
                    nop
                    osType      db 'testOS'
                    bpb
                    bps         dw  512
                    spc         db  8
                    rs          dw  1
                    fats        db  2
                    re          dw  512
                    ss          dw  0
                    media       db  0xf8
                    spfat       dw  0xc900
                    spt         dw  0x3f00
                    heads       dw  0x1000
                    hidden      dw  0x3f00, 0
                    ls          dw  0x5142, 0x0600
                    pdn         db  0x80
                    cheads      db  0
                    sig         db  0x29
                    serialno    dw  0xce13, 0x4630
                    label       db  'NO NAME'
                    fattype     db  'FAT32'
                    
BIOSEntryPoint:
                    jmp     0x0000:prepareRegisters

prepareRegisters:
                    cli                                     ;Preparatii pentru punerea in functiune a bootloader-ului;
                    xor     ax, ax                          ;Oprim intreruperile si setam ax impreuna cu registrii segment pe 0
                    mov     ds, ax
                    mov     ss, ax
                    mov     es, ax
                    mov     bp, 0x9000                      ;Creeam stack-ul intr-o zona de memorie departata
                    mov     sp, bp
                    sti                                     ;Repornim intreruperile
                    mov     byte [DRIVE_ID], dl             ;Salvam ID-ul drive-ului pe care suntem
                    
prog:                                                       ;Aici incepe efectiv programul bootloader
                    mov     bx, msj
                    call    printFromAdress                 ;Test 1 Hello World
                    mov     bx, endmsj                      ;Test 2 Hello World
                    call    printFromAdress
                    mov     bx, 0xdeef                      ;Test 3 conversie numar->string
                    call    printHexNumber
                    call    printHexNumber
                    mov     bx, 0x1234
                    call    printHexNumber
                    
haltCPU:
                    jmp     $                               ;Blocam procesorul
                    

                    

DRIVE_ID            db   0x00                               ;Salvam datele necesare
msj                 db   'Hello from the boot sector!', 10, 13, 0
endmsj              db   'Goodbye, boot sector!', 10, 13, 0
convertedHex        db   '0000', 0




%include "../src/printingroutine.asm"                        ;Fisiere extra folosite pentru organizare

times 510-($-$$) 	db      0                                ;Setam ce a mai ramas cu 0 si punem numarul 
                    dw      0xaa55                           ;special pentru BIOS la final
                    
                    
                    
                    
                    