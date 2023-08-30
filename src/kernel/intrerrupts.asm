bits 32
global _loadIDT
extern _isrHandler
extern _irqHandler

%macro ISR_NOERRORCODE 1
global _isr%1
_isr%1:
    push    byte 0                  ;In cazul in care intreruperea nu pune pe stack un cod de eroare trebuie sa punem noi
    push    byte %1
    jmp     isr_common_code
%endmacro

%macro ISR_ERRORCODE 1
global _isr%1
_isr%1:
    push    byte %1
    jmp     isr_common_code
%endmacro

%macro IRQ 2
global _irq%2
_irq%2:
    cli
    push    byte 0                  ;PIC nu pune coduri de eroare
    push    byte %1
    jmp     irq_common_code
%endmacro

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE   8
ISR_NOERRORCODE 9
ISR_ERRORCODE   10
ISR_ERRORCODE   11
ISR_ERRORCODE   12
ISR_ERRORCODE   13
ISR_ERRORCODE   14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_ERRORCODE   17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_ERRORCODE   21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31
IRQ             32,  0
IRQ             33,  1
IRQ             34,  2
IRQ             35,  3
IRQ             36,  4
IRQ             37,  5
IRQ             38,  6
IRQ             39,  7
IRQ             40,  8
IRQ             41,  9
IRQ             42,  10
IRQ             43,  11
IRQ             44,  12
IRQ             45,  13
IRQ             46,  14
IRQ             47,  15

;extern _idtEntries
_loadIDT:
    mov     eax, [esp + 4]                                  ; magie neagra periculoasa, structura se strica
    ;mov     [eax + 2], dword _idtEntries                    ; <- De ce gcc strica structura? FIX mai rau pentru structura stricata
    add     eax, 2                                          ; FIX pentru structura stricata: aliniam structura pe 16 si schimbam adresa cu un +2, functioneaza
    lidt    [eax]
    ret
    
isr_common_code:
    pusha
    
    mov     ax, ds
    push    eax
    
    mov     ax, 0x10                                        ;   <- problematic, structura pusa pe stack nu este okay, trebuie schimbat in pointer
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    
    call    _isrHandler
    
    pop     eax
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    
    popa
    add     esp, 8                      ; curatam stackul de byte-ul de eroare si byte-ul cu codul isr
    iret
    
    
irq_common_code:
    pusha
    
    mov     ax, ds
    push    eax
    
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    
    call    _irqHandler
    
    pop     eax
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    
    popa
    add     esp, 8
    sti
    iret