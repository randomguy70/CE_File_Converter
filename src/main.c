#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"

/* args
	-n <name of file to convert>
*/

/* file format
	http://merthsoft.com/linkguide/ti83+/fformat.html
*/

enum task {NONE, CONVERT_FILE, };

int convertFile(const char *fileName, const char *appvarName);
unsigned int appvar_checksum(uint8_t *arr, size_t size);

int main(int argc, char *argv[]) {
	/* arg loop counter */
	size_t i = 0;
	
	enum task task;
	bool convertedFile = false;
	
	FILE *fptr;
	char fileName[100]= {0};
	struct appvar appvar;
	char appvarName[9] = {0};
	
	for(i = 1; i<argc; i++)
	{
		if(argv[i][0] == '-' && argv[i][1] == 'n')
		{
			if(strlen(argv[2]) > 100)
			{
				printf("file names must be shorter than 101 characters\nAborting..\n");
				return 0;
			}
			
			task = CONVERT_FILE;
			strcpy(fileName, argv[2]);
			for(uint8_t ii=0; ii<strlen(argv[2]) && ii<9; ii++)
			{
				appvarName[ii] = argv[2][ii];
			}
			
			break;
		}
		task = NONE;
	}
	
	if(task == NONE)
	{
		printf("arg error: ", argv[1], "\n");
		printf(argString);
		printf("Aborting...\n");
		return 0;
	}
	
	if(task == CONVERT_FILE)
	{
		
	}
	
	
	
	return 0;
}

int writeAppvar(struct appvar *appvar, FILE *fptr)
{
	int writePos = 0;
	
	uint8_t output[APPVAR_MAX_FILE_SIZE];
	size_t outputSize;
	static const uint8_t header[APPVAR_HEADER_SIZE] = {0x2A,0x2A,0x54,0x49,0x38,0x33,0x46,0x2A,0x1A,0x0A,0x00};
	const char *comment = "Outputted by randomguy's file converter  ";
	uint16_t dataLen = appvar->data_len;
	uint16_t checkSum;
	
	
	for(int i=0; i<APPVAR_HEADER_SIZE; i++)
	{
		output[i+writePos] = header[i];
	}
	writePos+=APPVAR_HEADER_SIZE;
	
	for(int i=0; i<APPVAR_COMMENT_SIZE; i++)
	{
		output[i+writePos] = comment[i];
	}
	writePos += APPVAR_COMMENT_SIZE;
	
	
}

unsigned int appvar_checksum(uint8_t *arr, size_t size)
{
    uint16_t checksum = 0;
    size_t i;
	
    for (i = 0; i < size; ++i)
    {
        checksum += arr[APPVAR_VAR_HEADER_POS + i];
        checksum &= 0xffff;
    }

    return checksum;
}