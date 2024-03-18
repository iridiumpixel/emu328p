#include "stdio.h"

#include "atmega328p.h"
#include "defines.h"
#include "typedefs.h"

int main(int argc, char** argv)
{
    ATmega328p my_mcu;
    ATmega328p_init(&my_mcu);
    my_mcu.PROGRAM_MEMORY[0] = 0x24;
    my_mcu.PROGRAM_MEMORY[1] = 0x9A;
    my_mcu.PROGRAM_MEMORY[2] = 0x2C;
    my_mcu.PROGRAM_MEMORY[3] = 0x9A;
    ATmega328p_tick(&my_mcu);
    printf("%d\n", my_mcu.SRAM[0x20 + 0x4]);
    return 0;
}