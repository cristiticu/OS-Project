#include "utils.h"

void memcpy(u8* source, u8* destination, u32 nrbytes){
    for(u32 i = 0; i < nrbytes; i++)
        *(destination + i) = *(source + i);
}

void memset(u8* destination, u8 byte, u32 nrbytes){
    for(u32 i = 0; i < nrbytes; i++)
        *(destination + i) = byte;
}