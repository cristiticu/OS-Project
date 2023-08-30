#include "utils.h"

void kmemcpy(u8* const source, u8* const destination, const u32 nrbytes){
    for(u32 i = 0; i < nrbytes; i++)
        *(destination + i) = *(source + i);
}

void kmemset(u8* const destination, const u8 byte, const u32 nrbytes){
    for(u32 i = 0; i < nrbytes; i++)
        *(destination + i) = byte;
}