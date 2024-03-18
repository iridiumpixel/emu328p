#ifndef _IHEX_H
#define _IHEX_H

#include "stdint.h"

uint8_t* ihex_read(char* file_path, uint32_t* return_length);
void ihex_free(uint8_t* ihex);

#endif