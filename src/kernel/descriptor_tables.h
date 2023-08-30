#ifndef _DESCRIPTOR_TABLES_HEADER_FILE_
#define _DESCRIPTOR_TABLES_HEADER_FILE_

#include "data_types.h"

#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA 0x21
#define SLAVE_PIC_COMMAND 0xA0
#define SLAVE_PIC_DATA 0xA1


struct IDTentry{                       // o intrare in tabelul de descriptori de intrerupere. IDT-ul va contine 256 de intrari
    u16 base_addr_low;                  // Primii 2 bytes din adresa ISR-ului (intrerrupt service routine)
    u16 segment_selector;               // Un selector de segment valid
    u8 reserved;                        // Vor fi 0
    u8 flags;                           // Optiuni pentru isr, de obicei 0x8E
    u16 base_addr_high;                 // Ultimii 2 bytes din adresa isr-ului
}__attribute__((__packed__));




struct IDTdescriptor{                  // aceasta structura va fi incarcata in registrul IDT pentru a defini tabelul. Contine adresa de baza a tabelului + marimea, important - 1
    u16 __PADDING;                        // !!!2 necesar pentru compilator: se strica structura altfel, CHIAR SI CU ATTRIBUTE PACKED!!!
    u16 limit;                          //  !!!1 aceasta structura nu functioneaza, vezi intrerrupts.asm/loadIDT pentru un hack stupid
    u32 base;
}__attribute__((__packed__));



struct ISRregisters{
    u32 userds;
    u32 edi, esi, ebp, useless, ebx, edx, ecx, eax;
    u32 int_no;
    u32 error_code;
    u32 eip, cs, eflags, esp, userss;
}__attribute__((__packed__));

void initIDT();
void isrHandler();
void irqHandler();

typedef void (*IntrerruptRoutine)(struct ISRregisters);

void registerISR(u8 index, IntrerruptRoutine f);


extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


#endif