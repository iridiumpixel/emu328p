#include "stdint.h"

#include "atmega328p.h"

#ifndef _INSTRUCTION_HANDLERS_H
#define _INSTRUCTION_HANDLERS_H

void SBI(ATmega328p* MCU, uint32_t instruction_data);

#endif // _INSTRUCTION_HANDLERS_H