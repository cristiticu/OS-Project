#ifndef _SCREEN_DRIVER_HEADER_
#define _SCREEN_DRIVER_HEADER_

#include "../kernel/data_types.h"

#define VIDEO_ADRESS 0xA0000
#define WIDTH 320
#define HEIGHT 200
#define VIDEO_LIMIT WIDTH * HEIGHT

//Porturi I/O pentru ecran
#define PALLETE_MASK_PORT 0x3C6
#define PALLETE_READ_PORT 0x3C7
#define PALLETE_WRITE_PORT 0x3C8
#define PALLETE_DATA_PORT 0X3C9

//Definim niste culori standard, din nou in format RRRGGGBB
#define RED 0b11100000
#define GREEN 0b00011100
#define BLUE 0b00000011
#define YELLOW 0b11111100

struct RGB{
    u8 r;
    u8 g;
    u8 b;
};

// :clearScreen: functie ce va sterge continutul ecranului
void clearScreen();

// :initScreen: functie ce va initializa placa video cu o paleta de culori RRRGGGBB
void initScreen();

// :palleteSet: functie ce seteaza o paleta la un anumit index in placa video, nefolosit
void palleteSet(u8 index, struct RGB color);








#endif