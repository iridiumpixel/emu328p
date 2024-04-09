#ifndef _DEFINES_H
#define _DEFINES_H

#define ERROR_INSTRUCTION  0
#define INSTRUCTIONS_COUNT 10

// Memory layout of ATmega328p
#define MEMORY_ADRESS_START 0x0000 
#define MEMORY_ADRESS_END   0x3FFF 
#define MEMORY_SIZE         16384

#define GP_REGISTERS_MEMORY_START 0x0000 
#define GP_REGISTERS_MEMORY_END   0x001F 
#define GP_REGISTERS_SIZE         32

#define IO_REGISTERS_MEMORY_START 0x0020 
#define IO_REGISTERS_MEMORY_END   0x005F 
#define IO_REGISTERS_SIZE          64

#define EXT_IO_REGISTERS_MEMORY_START 0x0060 
#define EXT_IO_REGISTERS_MEMORY_END   0x00FF 
#define EXT_IO_REGISTERS_SIZE         160

#define SRAM_MEMORY_START 0x0100
#define SRAM_MEMORY_END   0x08ff
#define SRAM_SIZE         2048

#define PROGRAM_MEMORY_SIZE 2048

#define SREG_C 1 << 0
#define SREG_Z 1 << 1
#define SREG_N 1 << 2
#define SREG_V 1 << 3
#define SREG_S 1 << 4
#define SREG_H 1 << 5
#define SREG_T 1 << 6
#define SREG_I 1 << 7

#define MSB_8BIT 1 << 7
#define LSB      1

#endif