#ifndef _SCREEN_DRIVER_HEADER_
#define _SCREEN_DRIVER_HEADER_

#include "../kernel/data_types.h"

#define VIDEO_ADRESS 0xA0000                    // Adresa in RAM a memoriei folosite de VGA
#define BUFFER_VIDEO_ADDRESS 0x00100000         // Adresa unde se va face double-buffering.
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


// Definim o structura ce va contine font-ul utilizat sub forma unui bitmap.
// Folosit: https://github.com/dhepper/font8x8
extern const u8 FONT_BITMAP[128][8];

// Structura ce va retine litere, pentru printarea pe ecran in defavoarea selectarii proprii a pixelului
extern u8 LETTER_BUFFER[25][40];

extern u8 ROW_HANDLER;



// :clearScreen: functie ce va sterge continutul ecranului
void clearScreen();

// :clearRect: functie ce va sterge continului ecranului aflat intr-un dreptunghi. (prin sters se refera la inlocuirea cu culoarea setata in BACKGROUND)
void clearRect(const u16 x, const u16 y, const u16 width, const u16 height);

// :initScreen: functie ce va initializa placa video cu o paleta de culori RRRGGGBB. Aceasta functie trebuie apelata inaintea folosirii culorilor
void initScreen();

// :palleteSet: functie ce seteaza o paleta la un anumit index in placa video, nefolosit
void palleteSet(const u8 index, const u8 r, const u8 g, const u8 b);

// :renderPallete: functie ce va reda pe ecran paleta de culori in mod repetat;
void renderPallete();

// :printChar: functie ce va afisa pe ecran un caracter, coltul din stanga sus find la coordonatele x, y
void printChar(const u8 c, const u16 x, const u16 y, const u8 color);

// :printString: se foloseste de apeluri succesive ale lui printChar
void printString(u8* const str, const u16 x, const u16 y, const u8 color);

// :printNumber: afiseaza un numar pe ecran
void printNumber(u32 number, const u16 x, const u16 y, const u8 color);

// :background: functie ce va seta culoarea de baza a ecranului, va fi folosita in apeluri catre clearScreen sau clearRect
void background(const u8 color);

void refreshScreen();




#endif