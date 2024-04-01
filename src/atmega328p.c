#include "stdio.h"
#include "stdint.h"

#include "atmega328p.h"
#include "instruction.h"
#include "instruction_handlers.h"
#include "defines.h"
#include "typedefs.h"

Instruction instructions[INSTRUCTIONS_COUNT] = {
  {SBI,     0x9A00, 0xFF00, 2, 2},
  {RJMP,    0xC000, 0xF000, 2, 2},
  {RETI,    0x9518, 0xFFFF, 2, 4},
  {LDI,     0xE000, 0xF000, 2, 1},
  {STS,     0x9200, 0xFE0F, 4, 2},
};


Instruction INSTRUCTION_NOT_FOUND = {
  NULL,      0x0000, 0x0000, 0, 0
};


void ATmega328p_init(ATmega328p* MCU)
{
  (*MCU).PC = 0;
  (*MCU).SP = 0;

  (*MCU).tick_counter = 0;

  (*MCU).PORTA = 0;
  (*MCU).PORTB = 0;
  (*MCU).PORTC = 0;

  for (int i = 0; i < PROGRAM_MEMORY_SIZE; i++)
  {
    (*MCU).PROGRAM_MEMORY[i] = 0;
  }

  for (int i = 0; i < SRAM_SIZE; i++)
  {
    (*MCU).SRAM[i] = 0;
  }
}

uint16_t ATmega328p_fetch_16_bit_instruction(ATmega328p* MCU)
{
  // TODO: add exception handler
  uint16_t upper_half = (*MCU).PROGRAM_MEMORY[(*MCU).PC + 1] << 8;
  uint16_t lower_half = (*MCU).PROGRAM_MEMORY[(*MCU).PC + 0];
  return upper_half | lower_half;
}

uint32_t ATmega328p_fetch_32_bit_instruction(ATmega328p* MCU)
{
  // TODO: add exception handler
  uint32_t upper_half = ((*MCU).PROGRAM_MEMORY[(*MCU).PC + 1] << 24) | ((*MCU).PROGRAM_MEMORY[(*MCU).PC + 0] << 16); 
  uint32_t lower_half = ((*MCU).PROGRAM_MEMORY[(*MCU).PC + 3] << 8 ) | ((*MCU).PROGRAM_MEMORY[(*MCU).PC + 2]      );
  return upper_half | lower_half; 
}

Instruction ATmega328p_define_instruction(Instruction* instructions, uint32_t instruction)
{
  for (int i = 0; i < INSTRUCTIONS_COUNT; i++)
  {
    if ((instructions[i].opcode_mask & instruction) == instructions[i].opcode)
    {
    
      return instructions[i];
    } 
  }
  return INSTRUCTION_NOT_FOUND; 
}

void ATmega328p_tick(ATmega328p* MCU)
{
  (*MCU).tick_counter++;

  uint32_t instruction_data = ATmega328p_fetch_16_bit_instruction(MCU);
  Instruction instruction = ATmega328p_define_instruction(instructions, instruction_data);

  if (instruction.instruction_handler == NULL)
  {
    printf("Instruction not found, tick: %ld\n", (*MCU).tick_counter);
    return;
  }

  if (instruction.length == 4)
  {
    instruction_data = ATmega328p_fetch_32_bit_instruction(MCU);
  }

  instruction.instruction_handler(MCU, instruction_data);

  (*MCU).PC += instruction.length;
}

void ATmega328p_registers_print(ATmega328p* MCU)
{
  for (int i = 1; i < 33; i++)
  {
    printf("R%02d: %02x ", i, (*MCU).SRAM[i-1]);
    if (i != 0 && i % 8 == 0) printf("\n");
  }
  printf("\n");
  for (int i = 1; i < 65; i++)
  {
    printf("I%02d: %02x ", i, (*MCU).SRAM[i-1+32]);
    if (i != 0 && i % 8 == 0) printf("\n");
  }
  printf("\n");
}

void ATmega328p_memory_print(ATmega328p* MCU)
{
  for (int i = 0; i < 16; i++)
    printf("%02d ", i);
  printf("\n\n");
  for (int i = 1; i < 257; i++)
  {
    printf("%02x ", (*MCU).SRAM[i-1+SRAM_MEMORY_START]);
    if (i != 0 && i % 16 == 0) printf("\n");
  }
  printf("\n");
}
