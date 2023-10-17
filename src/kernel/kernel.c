#include "../drivers/screen.h"
#include "descriptor_tables.h"
#include "timer.h"

void start(){
    initIDT();
    initPaging();
    initScreen();
    
    registerTimedHandler(0, 0, &refreshScreen);
    initTimer(60);
    
    
    
    
    u32 xoff = 50;
    u32 yoff = 50;
    u32 seconds = 0;
    
    background(0x41);
    clearScreen();
    u8 color = 0x4B;
    
    
    while(1){
            clearRect(0, 0, 8 * 4, 8);
            seconds++;
            printNumber(GLOBAL_TICK, 0, 0, 0xCB);
        if(xoff < 256){
            printString("buckyOS", xoff,   yoff, color);
            printString("buckyOS", xoff+1, yoff+1, color + 0x20);
            printString("buckyOS", xoff+2, yoff+1, color + 0x40);
            printString("buckyOS", xoff+3, yoff+1, color + 0x60);
            xoff++;
        }
        else{
            color ++;
            yoff += 10;
            xoff = 0;
            if(yoff > 160)
                yoff = 3;
        }
        sleepTicks(1);
    }
}