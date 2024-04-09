#include "stdint.h"

#include "atmega328p.h"

#ifndef _INSTRUCTION_HANDLERS_H
#define _INSTRUCTION_HANDLERS_H

void   SBI(ATmega328p* MCU, uint32_t instruction_data);
void  RJMP(ATmega328p* MCU, uint32_t instruction_data);
void  RETI(ATmega328p* MCU, uint32_t instruction_data);
void   LDI(ATmega328p* MCU, uint32_t instruction_data);
void   STS(ATmega328p* MCU, uint32_t instruction_data);
void    IN(ATmega328p* MCU, uint32_t instruction_data);
void  SBRC(ATmega328p* MCU, uint32_t instruction_data);
void   CBI(ATmega328p* MCU, uint32_t instruction_data);
void   ORI(ATmega328p* MCU, uint32_t instruction_data);
void   SEI(ATmega328p* MCU, uint32_t instruction_data);


#endif // _INSTRUCTION_HANDLERS_H