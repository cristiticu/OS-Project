#include "screen.h"
#include "../kernel/low_level.h"
#include "../kernel/utils.h"

void palleteSet(u8 index, struct RGB color){
    port_out_byte(PALLETE_MASK_PORT, index);
    port_out_byte(PALLETE_DATA_PORT, color.r);
    port_out_byte(PALLETE_DATA_PORT, color.g);
    port_out_byte(PALLETE_DATA_PORT, color.b);
}

void initScreen(){
    port_out_byte(PALLETE_MASK_PORT, 0xff);
    port_out_byte(PALLETE_WRITE_PORT, 0);
    
    for(u8 i = 0; i < 255; i++){
        port_out_byte(PALLETE_DATA_PORT, (u8)(((i >> 5) & 0x7) * (256 / 8)) / 4);
        port_out_byte(PALLETE_DATA_PORT, (u8)(((i >> 2) & 0x7) * (256 / 8)) / 4);
        port_out_byte(PALLETE_DATA_PORT, (u8)(((i >> 0) & 0x3) * (256 / 4)) / 4);
    }
    port_out_byte(PALLETE_DATA_PORT, 0x3f);
    port_out_byte(PALLETE_DATA_PORT, 0x3f);
    port_out_byte(PALLETE_DATA_PORT, 0x3f);
}

void clearScreen(){
    initScreen();
    u8* vm = (u8*)VIDEO_ADRESS;
    
    u32 n = 0;
    for(u32 i = 0; i < HEIGHT; i++){
        memset(vm + i * WIDTH, (n + i) % 256, WIDTH);
    }
}