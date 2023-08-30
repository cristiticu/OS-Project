#include "paging.h"
#include "utils.h"

extern void loadPageDirectory(u32);

u32 pagingDirectory[1024] __attribute__((__aligned__(4096)));
u32 firstPageTable[1024] __attribute__((__aligned__(4096)));

void initPaging(){
    for(u16 i = 0; i < 1024; i++)
        pagingDirectory[i] = 0x2;
    for(u16 i = 0; i < 1024; i++)
        firstPageTable[i] = (i * 0x1000) | 0x3;
    pagingDirectory[0] = (u32)firstPageTable | 0x3;
    
    loadPageDirectory((u32)pagingDirectory);
}