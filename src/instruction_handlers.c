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
  (*MCU).SRAM[IO_REGISTERS_MEMORY_START + adress] |= bit_mask;
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
  (*MCU).SP += 2;
}

void LDI(ATmega328p* MCU, uint32_t instruction_data)
{
  // 1110 KKKK dddd KKKK
  uint16_t immidiate = (instruction_data & 0xF) | ((instruction_data & 0xF00) >> 4);
  uint16_t register_number = ((instruction_data & 0xF0) >> 4);
  // Loads to registers 16-31, therefore adding 16
  (*MCU).SRAM[GP_REGISTERS_MEMORY_START + register_number + 16] = immidiate;
}

void STS(ATmega328p* MCU, uint32_t instruction_data)
{
  // 1001 001d dddd 0000
  // kkkk kkkk kkkk kkkk
  uint32_t adress = instruction_data & 0x0000FFFF;
  uint32_t register_number = (instruction_data & 0x01F00000) >> 20;
  MCU->SRAM[adress] = MCU->SRAM[GP_REGISTERS_MEMORY_START + register_number];
}
