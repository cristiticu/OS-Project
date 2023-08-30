#include "timer.h"
#include "descriptor_tables.h"
#include "low_level.h"

volatile u32 GLOBAL_TICK = 0;
volatile u32 SLEEP_COUNTDOWN = 0;
u32 SELECTED_FREQUENCY = 0;

TimedObserver interestedParties[256];
u8 freeObserverIndex = 0;

static void advanceIndex(){
    while(interestedParties[freeObserverIndex].execute != 0)
        freeObserverIndex++;
}

void removeTimedHandler(u8 index){
    freeObserverIndex = index;
    interestedParties[index].execute = 0;
}

u8 registerTimedHandler(u8 ticksToWait, u8 ticksRemaining, TimedFunctionHandler execute){
    interestedParties[freeObserverIndex].ticksToWait = ticksToWait;
    interestedParties[freeObserverIndex].ticksRemaining = ticksRemaining;
    interestedParties[freeObserverIndex].execute = execute;
    u8 oldindex = freeObserverIndex;
    advanceIndex();
    return oldindex;
}

void timerTick(struct ISRregisters r){
    GLOBAL_TICK++;
    if(SLEEP_COUNTDOWN > 0)
        SLEEP_COUNTDOWN--;
    for(int i = 0; i < 256; i++)
        if(interestedParties[i].execute != 0)
            if(interestedParties[i].ticksRemaining == 0){
                interestedParties[i].ticksRemaining = interestedParties[i].ticksToWait;
                interestedParties[i].execute();
            }
            else
                interestedParties[i].ticksRemaining--;
}

void sleep(u32 miliseconds){
    SLEEP_COUNTDOWN = SELECTED_FREQUENCY * ((double)miliseconds / 1000.0);
    while(SLEEP_COUNTDOWN);
}

void sleepTicks(u32 ticks){
    SLEEP_COUNTDOWN = ticks;
    while(SLEEP_COUNTDOWN);
}

void initTimer(u32 frequency){
    SELECTED_FREQUENCY = frequency;
    registerISR(32, &timerTick);
    u16 frequencyDivide = 1193182 / frequency;           // Va trebui sa setam impartirea frecventei PIT-ului la acest numar ca sa obtiner frecventa dorita.
                                                         // PIT-ul are 3 canale care genereasa puls la frecventa 1.193182 MHz.
    portOut_b(PIT_COMMAND, 0x34);                    // PIT-ul are 3 canale, iar canalul 0 este conectat la IRQ0
    portOut_b(PIT_CH_0, frequencyDivide & 0xFF);
    portOut_b(PIT_CH_0, (frequencyDivide >> 8) & 0xFF);
}                                                       
                                                        


                                                        