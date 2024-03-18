#include "stdint.h"

#include "typedefs.h"
#include "defines.h"

#ifndef _ATMEGA328P_H
#define _ATMEGA328P_H



void ATmega328p_init(ATmega328p* MCU);

void ATmega328p_tick(ATmega328p* MCU);

uint16_t ATmega328p_fetch_16_bit_opcode(ATmega328p* MCU);

uint32_t ATmega328p_fetch_32_bit_opcode(ATmega328p* MCU);

Instruction ATmega328p_define_instruction(
            Instruction* instructions, uint32_t instruction);

#endif //_ATMEGA328P_H