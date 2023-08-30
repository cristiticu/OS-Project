#include "low_level.h"

u8 portIn_b(const u16 port){
    u8 result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void portOut_b(const u16 port, const u8 byte){
    asm("outb %1, %0" : : "dN" (port), "a" (byte));
}

u16 portIn_w(const u16 port){
    u16 result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void portOut_w(const u16 port, const u16 word){
    __asm__("out %%ax, %%dx" : : "a" (word), "d" (port));
}

