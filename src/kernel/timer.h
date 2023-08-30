#ifndef _TIMER_KERNEL_HEADER_
#define _TIMER_KERNEL_HEADER_

#include "data_types.h"

#define PIT_CH_0 0x40                           // Canalul 0 din PIT este rezervat pentru intreruperea sistemului la intervale de timp definite. Foloseste IRQ0
#define PIT_CH_1 0x41                           // Canalul 1 este nefolosit si chiar NEFUNCTIONAL in unele cazuri
#define PIT_CH_2 0x42                           // Canalul 2 este folosit pentru controlul boxelor
#define PIT_COMMAND 0x43                        // La aceasta adresa PIT-ul primeste comenzi

typedef void (*TimedFunctionHandler)(void);

typedef struct {                                // Un tip de data ce reprezinta o functie ce se doreste a fi executata la un interval de timp definit
    u8 ticksToWait;                             // Exemplu: functia de refreshScreen din screen.h este apelata la fiecare tick, avand tiskToWait = 0
    u8 ticksRemaining;
    TimedFunctionHandler execute;
} TimedObserver;


extern volatile u32 GLOBAL_TICK;
extern volatile u32 COUNTDOWN;                 
extern u32 SELECTED_FREQUENCY;


// :initTimer: functie ce va initializa timer-ul PIT la frecventa dorita. Mai precis, va seta canalul 0 pe o anumita frecventa
void initTimer(u32 frequency);

// :sleep: va opri executia codului pentru un numar de milisecunde.
void sleep(u32 miliseconds);

// :sleepTicks: va opri executia codului pentru un nr de ticks
void sleepTicks(u32 ticks);

// :registerTimedHandler: o functie ce va adauga o functie interesata de timer. se va executa cand ticksremaining va fi 0, pornind de la tickstowait
// :returns: returneaza indexul din lista functiilor inregistrate
u8 registerTimedHandler(u8 ticksToWait, u8 ticksRemaining, TimedFunctionHandler execute);

// :removeTimedHandler: functie ce va sterge o functie de rulat la ticks de la un anumit index
void removeTimedHandler(u8 index);

#endif