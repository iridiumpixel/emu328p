#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

#include "atmega328p.h"
#include "instruction_handlers.h"


void SBI(ATmega328p* MCU, uint32_t instruction_data)
{
  // 10011010AAAAAkkk
  uint8_t adress = (instruction_data & 0x00F8) >> 3;
  uint8_t bit    =  instruction_data & 0x0007;
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

void IN(ATmega328p* MCU, uint32_t instruction_data)
{
  // 1011 0AAd dddd AAAA
  uint8_t register_number = (instruction_data & 0x01F0) >> 4;
  uint8_t memory_adress = ((instruction_data & 0x600) >> 4) | (instruction_data & 0xF);
  MCU->SRAM[GP_REGISTERS_MEMORY_START + register_number] = MCU->SRAM[memory_adress];
}


void SBRC(ATmega328p* MCU, uint32_t instruction_data)
{
  // 1111 110r rrrr 0bbb
  uint8_t bit = instruction_data & 0x7;
  uint8_t register_number = (instruction_data & 0x1F0) >> 4;
  if ((MCU->SRAM[GP_REGISTERS_MEMORY_START + register_number] & bit) == 0)
  {
    // Skip next instruction
    MCU->skip_next_instruction = true;
  }
}


void CBI(ATmega328p* MCU, uint32_t instruction_data)
{
  // 10011010AAAAAkkk
  uint8_t adress = (instruction_data & 0x00F8) >> 3;
  uint8_t bit    =  instruction_data & 0x0007;
  uint8_t bit_mask = 1 << (bit - 1);
  (*MCU).SRAM[IO_REGISTERS_MEMORY_START + adress] &= (~bit_mask);
}

void ORI(ATmega328p* MCU, uint32_t instruction_data)
{
  // 0110 KKKK dddd KKKK
  uint32_t immidiate = ((instruction_data & 0xF00) >> 4) | (instruction_data & 0xF);
  // since 16 <= d <= 31 adding 16 to 4-bit number is necessary
  uint8_t register_number = (instruction_data & 0xF0) >> 4 + 16;
  uint8_t op_result = MCU->SRAM[GP_REGISTERS_MEMORY_START + register_number] | immidiate;
  MCU->SRAM[GP_REGISTERS_MEMORY_START + register_number] = (
    MCU->SRAM[GP_REGISTERS_MEMORY_START + register_number] = op_result);
  
  MCU->SREG &= ~SREG_V;
  // Most significant byte test
  MCU->SREG &= (op_result & MSB_8BIT);
  uint8_t sreg_z_test_result;
  for (int i = 0; i < 8; i++)
  {
    sreg_z_test_result &= ((op_result >> i) & 1);
  }

  if (sreg_z_test_result == 0)
  {
    MCU->SREG |= SREG_Z;
  }
  else
  {
    MCU->SREG &= ~SREG_Z;
  }

}


void SEI(ATmega328p* MCU, uint32_t instruction_data)
{
  // 1001 0100 0111 1000
  // Should execute the instruction following SEI
  MCU->SREG |= SREG_I;
}