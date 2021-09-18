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

/*
int writeAppvar(struct appvar *appvar, FILE *fptr)
{
	int writePos = 0;
	
	uint8_t output[APPVAR_MAX_FILE_SIZE];
	size_t outputSize;
	static const uint8_t header[APPVAR_HEADER_SIZE] = {0x2A,0x2A,0x54,0x49,0x38,0x33,0x46,0x2A,0x1A,0x0A,0x00};
	const char *comment = "Outputted by randomguy's file converter  ";
	uint16_t dataLen = appvar->data_len;
	const uint16_t variableHeader = 11;
	uint16_t variableDataLen;
	uint8_t variableIDType = APPVAR_TYPE_FLAG;
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
	
	output[writePos++] = appvar->data_len && 0xff;
	output[writePos++] = appvar->data_len && 0xff;
	
	// data section, consists of 1 variable entry
	output[writePos++] = variableHeader && 0xff;
	output[writePos++] = variableHeader && 0xff;
}
*/

/* thank you, Mateo! */
int appvar_write(struct appvar *a, FILE *fdv)
{
	unsigned int checksum;
	static const uint8_t file_header[11] =
		{ 0x2A,0x2A,0x54,0x49,0x38,0x33,0x46,0x2A,0x1A,0x0A,0x00 };
	
	static uint8_t output[APPVAR_MAX_FILE_SIZE];
	size_t name_size;
	size_t file_size;
	size_t data_size;
	size_t varb_size;
	size_t var_size;
	size_t size;
	
   size = a->size;
	
	if (a->size > APPVAR_MAX_DATA_SIZE)
	{
		LOG_ERROR("Too much data for AppVar \'%s\'.\n", a->name);
			return -1;
	}
	
	file_size = a->size + APPVAR_DATA_POS + APPVAR_CHECKSUM_LEN;
	data_size = a->size + APPVAR_VAR_HEADER_LEN + APPVAR_VARB_SIZE_LEN;
	var_size = a->size + APPVAR_VARB_SIZE_LEN;
	varb_size = a->size;

	name_size = strlen(a->name) > 8 ? 8 : strlen(a->name);

	memcpy(output + APPVAR_FILE_HEADER_POS, file_header, sizeof file_header);
	memcpy(output + APPVAR_NAME_POS, a->name, name_size);
	memcpy(output + APPVAR_DATA_POS, a->data, varb_size);
	
	output[APPVAR_VAR_HEADER_POS] = APPVAR_MAGIC;
	output[APPVAR_TYPE_POS] = APPVAR_TYPE_FLAG;
	output[APPVAR_ARCHIVE_POS] = APPVAR_ARCHIVE_FLAG;

	output[APPVAR_DATA_SIZE_POS + 0] = (data_size >> 0) & 0xff;
	output[APPVAR_DATA_SIZE_POS + 1] = (data_size >> 8) & 0xff;

	output[APPVAR_VARB_SIZE_POS + 0] = (varb_size >> 0) & 0xff;
	output[APPVAR_VARB_SIZE_POS + 1] = (varb_size >> 8) & 0xff;

	output[APPVAR_VAR_SIZE0_POS + 0] = (var_size >> 0) & 0xff;
	output[APPVAR_VAR_SIZE0_POS + 1] = (var_size >> 8) & 0xff;
	output[APPVAR_VAR_SIZE1_POS + 0] = (var_size >> 0) & 0xff;
	output[APPVAR_VAR_SIZE1_POS + 1] = (var_size >> 8) & 0xff;

	checksum = appvar_checksum(output, data_size);

	output[APPVAR_DATA_POS + varb_size + 0] = (checksum >> 0) & 0xff;
	output[APPVAR_DATA_POS + varb_size + 1] = (checksum >> 8) & 0xff;

	return fwrite(output, file_size, 1, fdv) == 1 ? 0 : -1;
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