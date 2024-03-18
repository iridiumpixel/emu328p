#include "stdint.h"

#include "atmega328p.h"
#include "instruction_handlers.h"


void SBI(ATmega328p* MCU, uint32_t instruction_data)
{
  // Set bit in I/O Register
  // 1001 1010 00010 0100
  //&0000 0000 11111 1000
  
  uint8_t adress = (instruction_data & 0x00F8) >> 3;
  uint8_t bit    =  instruction_data & 0x0007;
  uint8_t bit_mask = 1 << (bit - 1);
  (*MCU).SRAM[adress + IO_REGISTERS_MEMORY_START] |= bit_mask;
}