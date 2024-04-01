#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

#include "defines.h"
#include "stdint.h"

typedef struct 
{
  // Memory
  uint8_t PROGRAM_MEMORY[PROGRAM_MEMORY_SIZE];
  uint8_t SRAM[SRAM_SIZE];
  uint16_t PC; // Program counter
  uint32_t SP; // Stack pointer

  uint64_t tick_counter;

  // ¨Pins¨ for debugging
  uint8_t PORTA;
  uint8_t PORTB;
  uint8_t PORTC;
} ATmega328p;

typedef struct
{
  void (*instruction_handler)(ATmega328p* MCU, uint32_t opcode);
  uint32_t opcode;
  uint32_t opcode_mask; 
  uint8_t  length;
  uint8_t  cycles;
} Instruction;


#endif