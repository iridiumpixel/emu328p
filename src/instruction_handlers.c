#include "stdint.h"
#include "stdio.h"

#include "atmega328p.h"
#include "instruction_handlers.h"


void SBI(ATmega328p* MCU, uint32_t instruction_data)
{
  // 10011010AAAAAkkk
  uint8_t adress = (instruction_data & 0x00F8) >> 3;
  uint8_t bit    =  instruction_data & 0x0007;
  printf("SBI\t%x,\t%x\n", adress, bit);
  uint8_t bit_mask = 1 << (bit - 1);
  (*MCU).SRAM[adress + IO_REGISTERS_MEMORY_START] |= bit_mask;
}

void RJMP(ATmega328p* MCU, uint32_t instruction_data)
{
  // 1100kkkkkkkkk
  int16_t r_adress_words = instruction_data & 0x0FFF;
  // Signed extension
  uint8_t to_copy_bit = (r_adress_words & 0x0800) >> 11;
  r_adress_words |= (to_copy_bit == 0 ? 0x0000 : 0xF000);
  int16_t r_adress_bytes = r_adress_words * 2;
  printf("RJMP\t.+(%d)\t\t; 0x%08x\n", r_adress_bytes, r_adress_bytes);
  (*MCU).PC = (*MCU).PC + r_adress_bytes;
}

void RETI(ATmega328p* MCU, uint32_t instruction_data)
{
  (*MCU).PC = (uint16_t)((*MCU).SRAM[(*MCU).SP + 1]) | (uint16_t)((*MCU).SRAM[(*MCU).SP] << 8);
  (*MCU).PC += 2;
}

