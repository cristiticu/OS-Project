#ifndef _LOW_LEVEL_UTILITARIES_HEADER_
#define _LOW_LEVEL_UTILITARIES_HEADER_

#include "data_types.h"

// Functii low level pentru comunicare prin porturi I/O

// :port_in_byte: Functie ce va citi un anumit port si va returna byte-ul citit
// :param port: portul dorit, pe 2 bytes
u8 port_in_byte(u16 port);

// :port_out_byte: Functie ce va scrie un byte la un anumit port
// :param port: portul dorit, pe 2 bytes
// :param byte: byte-ul ce se doreste scris la port
void port_out_byte(u16 port, u8 byte);

// :port_in_word: Functie ce va citi un anumit port si va returna word-ul citit
// :param port: portul dorit, pe 2 bytes
u16 port_in_word(u16 port);

// :port_out_word: Functie ce va scrie un word la un anumit port
// :param port: portul dorit, pe 2 bytes
// :param word: word-ul ce se doreste scris la port
void port_out_word(u16 port, u16 word);

#endif