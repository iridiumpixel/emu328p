#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "ihex.h"

#define MIN_IHEX_LINE_LENGTH 9
#define MAX_IHEX_LINE_LENGTH 536

#define START_CODE_LENGTH 1
#define NUMBER_OF_BYTES_LENGTH 2
#define ADRESS_LENGTH 4
#define RECORD_TYPE_LENGTH 2
#define CHECKSUM_LENGTH 2


uint8_t* ihex_read(char* file_path, uint32_t* return_length)
{
  FILE* ihex_file = fopen(file_path, "r");
  char ihex_line[MAX_IHEX_LINE_LENGTH];
  uint32_t line_counter = 0;

  char line_number_of_bytes[NUMBER_OF_BYTES_LENGTH + 1];
  char line_adress[ADRESS_LENGTH + 1];
  char line_record_type[RECORD_TYPE_LENGTH + 1]; 
  //char line_checksum[CHECKSUM_LENGTH + 1];
  char data_byte[3];


  uint8_t* ihex_data = NULL;
  size_t length = 0;
  uint32_t ihex_data_pointer = 0;

  // strol() requires long int type
  int32_t line_number_of_bytes_converted;
  int32_t line_adress_converted;
  int32_t line_record_type_converted;
  
  if (ihex_file == NULL)
  {
    printf("Cant open IHEX file");
    return NULL;
  }

  rewind(ihex_file);

  while (fgets(ihex_line, MAX_IHEX_LINE_LENGTH, ihex_file))
  {
    if (strlen(ihex_line) < MIN_IHEX_LINE_LENGTH)
    {
      printf("Line %d is too short!\n", line_counter);
      return NULL;
    }

    if (ihex_line[0] != ':')
    {
      printf("Error on line:%d:\nExpected ':', got %c\n", 
             line_counter, ihex_line[0]);
      return NULL; 
    }

    for (int i = 0; i < NUMBER_OF_BYTES_LENGTH; i++)
    {
      const int OFFSET = START_CODE_LENGTH;
      line_number_of_bytes[i] = ihex_line[i + OFFSET];
    }
    line_number_of_bytes[NUMBER_OF_BYTES_LENGTH] = '\0';

    for (int i = 0; i < ADRESS_LENGTH; i++)
    {
      const int OFFSET = START_CODE_LENGTH + NUMBER_OF_BYTES_LENGTH;
      line_adress[i] = ihex_line[i + OFFSET];
    }
    line_adress[ADRESS_LENGTH] = '\0';

    for (int i = 0; i < RECORD_TYPE_LENGTH; i++)
    {
      const int OFFSET = START_CODE_LENGTH + NUMBER_OF_BYTES_LENGTH + ADRESS_LENGTH;
      line_record_type[i] = ihex_line[i + OFFSET];
    }
    line_record_type[RECORD_TYPE_LENGTH] = '\0';

    line_number_of_bytes_converted = strtol(line_number_of_bytes, NULL, 16);
    
    line_adress_converted = strtol(line_adress, NULL, 16);
    // Here to get rid of compiler warning
    // Ill remove it when needed
    line_adress_converted++;

    line_record_type_converted = strtol(line_record_type, NULL, 16);

    if (line_record_type_converted == 0x00)
    {
      length += line_number_of_bytes_converted;
      ihex_data = realloc(ihex_data, length); 

      data_byte[3] = '\0';

      for (int i = 0; i < line_number_of_bytes_converted * 2; i += 2)
      {
        const int OFFSET = START_CODE_LENGTH + NUMBER_OF_BYTES_LENGTH + ADRESS_LENGTH + RECORD_TYPE_LENGTH;
        data_byte[0] = ihex_line[i + OFFSET];
        data_byte[1] = ihex_line[i + OFFSET + 1];
        ihex_data[ihex_data_pointer] = strtol(data_byte, NULL, 16);
        ihex_data_pointer++;
      }
    }

  }

  (*return_length) = length;
  return ihex_data;
}


void ihex_free(uint8_t* ihex)
{
  free(ihex);
}
