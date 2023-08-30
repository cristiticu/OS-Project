#include "descriptor_tables.h"
#include "../drivers/screen.h"
#include "utils.h"
#include "low_level.h"

extern void loadIDT(u32* const);

struct IDTentry idtEntries[256];
struct IDTdescriptor idtDesc;
IntrerruptRoutine intrerruptRoutines[256];

void registerISR(u8 index, IntrerruptRoutine f){
    intrerruptRoutines[index] = f;
}

static void modifyIDTEntry(u8 index, u32 base, u16 seg, u8 flags){              //Functia va seta un anumit entry din IDT
    idtEntries[index].base_addr_low =(u16)(base & 0xFFFF);                      //Luam partea low din adresa functiei de intrerupere
    idtEntries[index].base_addr_high =(u16)((base >> 16) & 0xFFFF);             //Luam partea high din adresa functiei de intrerupere
    idtEntries[index].segment_selector = seg;
    idtEntries[index].flags = flags;                                            //Flags: pentru ring 0, trebuie 0x8E
    idtEntries[index].reserved = 0;
}

void sendEOItoPIC(u8 int_no){
    if(int_no > 39)
        portOut_b(SLAVE_PIC_COMMAND, 0x20);                                 // Trimitem comenzile de terminare de intrerupere
    portOut_b(MASTER_PIC_COMMAND, 0x20);
        
}

void initPIC(){
    portOut_b(SLAVE_PIC_COMMAND, 0x11);                                     // Comanda de initializare PIC
    portOut_b(MASTER_PIC_COMMAND, 0x11);
    
    portOut_b(MASTER_PIC_DATA, 0x20);                                       // offset-urile de folosit pentru IRQ-uri, de la 0x20 la 0x2F
    portOut_b(SLAVE_PIC_DATA, 0x28);
    
    portOut_b(MASTER_PIC_DATA, 0x4);                                        //Spunem primului PIC ca are pic secundar pe pin 3 (0000 00100)
    portOut_b(SLAVE_PIC_DATA, 0x2);
    
    portOut_b(MASTER_PIC_DATA, 0x1);
    portOut_b(SLAVE_PIC_DATA, 0x1);
}    

void isrHandler(struct ISRregisters r){
    printString("Intrerupere activata!", 0, 0, RED);
    printNumber(r.int_no, 0, 8, RED);
    asm volatile("hlt");
}

void irqHandler(struct ISRregisters r){
    sendEOItoPIC(r.int_no);
    if(intrerruptRoutines[r.int_no] != 0)
        intrerruptRoutines[r.int_no](r);
}


void initIDT(){
    idtDesc.limit = sizeof(struct IDTentry) * 256 - 1;                     // Setam informatiile despre IDT in descriptor, pentru a fi incarcat in idtr
    idtDesc.base = (u32)idtEntries;
    
    kmemset((u8* const)&idtEntries, 0, sizeof(struct IDTentry) * 256);
    kmemset((u8* const)&intrerruptRoutines, 0, sizeof(IntrerruptRoutine) * 256);
    modifyIDTEntry( 0, (u32)isr0 , 0x08, 0x8E);
    modifyIDTEntry( 1, (u32)isr1 , 0x08, 0x8E);
    modifyIDTEntry( 2, (u32)isr2 , 0x08, 0x8E);
    modifyIDTEntry( 3, (u32)isr3 , 0x08, 0x8E);
    modifyIDTEntry( 4, (u32)isr4 , 0x08, 0x8E);
    modifyIDTEntry( 5, (u32)isr5 , 0x08, 0x8E);
    modifyIDTEntry( 6, (u32)isr6 , 0x08, 0x8E);
    modifyIDTEntry( 7, (u32)isr7 , 0x08, 0x8E);
    modifyIDTEntry( 8, (u32)isr8 , 0x08, 0x8E);
    modifyIDTEntry( 9, (u32)isr9 , 0x08, 0x8E);
    modifyIDTEntry(10, (u32)isr10, 0x08, 0x8E);
    modifyIDTEntry(11, (u32)isr11, 0x08, 0x8E);
    modifyIDTEntry(12, (u32)isr12, 0x08, 0x8E);
    modifyIDTEntry(13, (u32)isr13, 0x08, 0x8E);
    modifyIDTEntry(14, (u32)isr14, 0x08, 0x8E);
    modifyIDTEntry(15, (u32)isr15, 0x08, 0x8E);
    modifyIDTEntry(16, (u32)isr16, 0x08, 0x8E);
    modifyIDTEntry(17, (u32)isr17, 0x08, 0x8E);
    modifyIDTEntry(18, (u32)isr18, 0x08, 0x8E);
    modifyIDTEntry(19, (u32)isr19, 0x08, 0x8E);
    modifyIDTEntry(20, (u32)isr20, 0x08, 0x8E);
    modifyIDTEntry(21, (u32)isr21, 0x08, 0x8E);
    modifyIDTEntry(22, (u32)isr22, 0x08, 0x8E);
    modifyIDTEntry(23, (u32)isr23, 0x08, 0x8E);
    modifyIDTEntry(24, (u32)isr24, 0x08, 0x8E);
    modifyIDTEntry(25, (u32)isr25, 0x08, 0x8E);
    modifyIDTEntry(26, (u32)isr26, 0x08, 0x8E);
    modifyIDTEntry(27, (u32)isr27, 0x08, 0x8E);
    modifyIDTEntry(28, (u32)isr28, 0x08, 0x8E);
    modifyIDTEntry(29, (u32)isr29, 0x08, 0x8E);
    modifyIDTEntry(30, (u32)isr30, 0x08, 0x8E);
    modifyIDTEntry(31, (u32)isr31, 0x08, 0x8E);
    
    modifyIDTEntry(32, (u32)irq0 , 0x08, 0x8E);
    modifyIDTEntry(33, (u32)irq1 , 0x08, 0x8E);
    modifyIDTEntry(34, (u32)irq2 , 0x08, 0x8E);
    modifyIDTEntry(35, (u32)irq3 , 0x08, 0x8E);
    modifyIDTEntry(36, (u32)irq4 , 0x08, 0x8E);
    modifyIDTEntry(37, (u32)irq5 , 0x08, 0x8E);
    modifyIDTEntry(38, (u32)irq6 , 0x08, 0x8E);
    modifyIDTEntry(39, (u32)irq7 , 0x08, 0x8E);
    modifyIDTEntry(40, (u32)irq8 , 0x08, 0x8E);
    modifyIDTEntry(41, (u32)irq9 , 0x08, 0x8E);
    modifyIDTEntry(42, (u32)irq10, 0x08, 0x8E);
    modifyIDTEntry(43, (u32)irq11, 0x08, 0x8E);
    modifyIDTEntry(44, (u32)irq12, 0x08, 0x8E);
    modifyIDTEntry(45, (u32)irq13, 0x08, 0x8E);
    modifyIDTEntry(46, (u32)irq14, 0x08, 0x8E);
    modifyIDTEntry(47, (u32)irq15, 0x08, 0x8E);
    
    loadIDT((u32* const)&idtDesc);
    initPIC();
    asm volatile("sti");
}