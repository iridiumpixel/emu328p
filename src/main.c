#include "stdio.h"

#include "atmega328p.h"
#include "defines.h"
#include "typedefs.h"
#include "ihex.h"

int main(int argc, char** argv)
{
    uint32_t length;
    uint8_t* data = ihex_read("avr_assembly_test/test.hex", &length);
    for (int i = 0; i < length; i++)
    {
        printf("%02x\t", data[i]);
        if (length % 8 == 0) printf("\n");
    }
    ihex_free(data);
    return 0;
}