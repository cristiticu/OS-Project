#include "low_level.h"

u8 port_in_byte(u16 port){
    u8 result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_out_byte(u16 port, u8 byte){
    asm("outb %1, %0" : : "dN" (port), "a" (byte));
}

u16 port_in_word(u16 port){
    u16 result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_out_word(u16 port, u16 word){
    __asm__("out %%ax, %%dx" : : "a" (word), "d" (port));
}

