#ifndef _UTILITARIES_HEADER_
#define _UTILITARIES_HEADER_

#include "data_types.h"

void kmemcpy(u8* const source, u8* const destination, const u32 nrbytes);

void kmemset(u8* const destination, const u8 byte, const u32 nrbytes);

#endif