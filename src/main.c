#include "stdio.h"

#include "atmega328p.h"
#include "defines.h"
#include "typedefs.h"
#include "ihex.h"

int main(int argc, char** argv)
{
    uint32_t length;
    uint8_t* ihex_data = ihex_read("avr_assembly_test/test1.hex", &length);

    ATmega328p MCU;
    ATmega328p_init(&MCU);
    for(int i = 0; i < length; i++)
    {
        MCU.PROGRAM_MEMORY[i] = ihex_data[i];
    }
    int32_t c;
    scanf("%d", &c);
    while (c != 20)
    {
        printf("Tick: %ld\n", MCU.tick_counter);
        if (c == 0)
            ATmega328p_tick(&MCU);
        if (c == 1)
            ATmega328p_registers_print(&MCU);
        if (c == 2)
            ATmega328p_memory_print(&MCU);
        if (c == 3)
            printf("PC: %d\n", (MCU).PC);
        scanf("%d", &c);
    }
    ihex_free(ihex_data);
    return 0;
}
