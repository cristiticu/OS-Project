org     0x7c00
bits    16

                    jmp short   BIOSEntryPoint
                    nop
                    osType      db 'testOS'
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
                    
DRIVE_ID                db   0x00                               ;Salvam datele necesare
WOB_TEXT                db   0x0f
VIDEO_MEMORY            equ  0xb8000
KERNEL_OFFSET           equ  0x1000
msj                     db   'Pornit in Mod Real pe 16 biti', 10, 13, 0
convertedHex            db   '0000', 0



GDT_START:                                                                          ;Global Descriptor Table - structura de date necesara
GDT_NULL:                                                                           ;trecerii procesorului pe 32 de biti.
                        dq      0x000000                                            ;Prima intrare va fi null. Vom folosi stilul de overlap
GDT_CODE:                                                                           ;adica vor fi initial 2 segmente: code si data care utilizeaza toti 4gb de memorie
                        dw      0xffff      ;Limita de segment-> full
                        dw      0x0000      ;adresa de baza partea 1 -> 0
                        db      0x00        ;adresa de baza partea 2 -> 0
                        db      10011010b   ;primul set de flaguri, setari pentru segment de cod
                        db      11001111b   ;impartit pe jumate, adica primii 4 biti sunt tot flaguri, ultimii 4 fac parte din limita, adica inca un f
                        db      0x00        ;adresa de baza partea 3 -> 0
GDT_DATA:
                        dw      0xffff      ;Limita de segment-> full
                        dw      0x0000      ;adresa de baza partea 1 -> 0
                        db      0x00        ;adresa de baza partea 2 -> 0
                        db      10010010b   ;primul set de flaguri, setari pentru segment de data
                        db      11001111b   ;impartit pe jumate, adica primii 4 biti sunt tot flaguri, ultimii 4 fac parte din limita, adica inca un f
                        db      0x00
GDT_END:
GDT_DESCRIPTOR:
                        dw      GDT_END - GDT_START - 1
                        dd      GDT_START
CODE_SEGMENT            equ     GDT_CODE - GDT_START
DATA_SEGMENT            equ     GDT_DATA - GDT_START
                    
%include "../src/boot/printingroutine.asm"                       ;Fisiere extra folosite pentru organizare


              
prepareRegisters:
                    cli                                     ;Preparatii pentru punerea in functiune a bootloader-ului;
                    xor     ax, ax                          ;Oprim intreruperile si setam ax impreuna cu registrii segment pe 0
                    mov     ds, ax
                    mov     ss, ax
                    mov     es, ax
                    mov     bp, word 0x9000                 ;Creeam stack-ul intr-o zona de memorie departata
                    mov     sp, bp
                    sti                                     ;Repornim intreruperile
                    mov     byte [DRIVE_ID], dl             ;Salvam ID-ul drive-ului pe care suntem
                    
progStart:                                                  ;Aici incepe efectiv programul bootloader
                    mov     bx, msj
                    call    printFromAdress                 ;Test 1 Hello World  
                    mov     bx, KERNEL_OFFSET               ;Incarcam kernel-ul scris in C la adresa 0x1000
                    mov     dl, byte [DRIVE_ID]             ;Driveul salvat
                    mov     ah, 0x02                        ;Citim
                    mov     al, 15
                    mov     ch, 0
                    mov     dh, 0
                    mov     cl, 2
                    int     0x13
                    cli                                     ;Incepem schimbarea catre 32 de biti
                    lgdt    [GDT_DESCRIPTOR]                ;setam LGDT
                    mov     eax, cr0
                    or      eax, 0x1
                    mov     cr0, eax                        ;Acum, procesorul este pe 32 de biti dar trebuie sa eliberam pipeline-ul, executand un far jump
                    jmp     CODE_SEGMENT:configureaza32
                            
haltCPU:
                    jmp     $                               ;Blocam procesorul
                    

                    
bits 32

configureaza32:                                         ;Configuram segmentele directoare
                    mov     ax, DATA_SEGMENT
                    mov     ds, ax
                    mov     ss, ax
                    mov     es, ax
                    mov     fs, ax
                    mov     gs, ax
                    
                    mov     ebp, 0x90000
                    mov     esp, ebp
                    
                    call    startModProtejat32
                    
startModProtejat32:                                     ;Oficial, mod protejat 32 biti
                    call    KERNEL_OFFSET
                    jmp     $


times 510-($-$$) 	db      0                                   ;Setam ce a mai ramas cu 0 si punem numarul 
                    dw      0xaa55                              ;special pentru BIOS la final
                    
                    
                
                    
                