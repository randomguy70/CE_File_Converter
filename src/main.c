#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"

/* args
	-n <name of file to convert>
*/

/* file format
	http://merthsoft.com/linkguide/ti83+/fformat.html
*/

enum task {NONE, CONVERT_FILE, };

int convertFile(const char *fileName, const char *appvarName);
int appvar_write(struct appvar *a, FILE *fdv);
unsigned int appvar_checksum(uint8_t *arr, size_t size);
long int findSize(char *file_name);

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
		if(argc <=1 )
		{
			printf("Error: No args inputted\n%s\n", argString);
		}
		
		if(argv[i][0] == '-' && argv[i][1] == 'n')
		{
			if(strlen(argv[2]) > 100)
			{
				printf("file names must be shorter than 101 characters\nAborting..\n");
				return 0;
			}
			
			strcpy(fileName, argv[2]);
			strcat(fileName, ".8xp");
			fptr = fopen(fileName, "w+");
			
			if(!fptr)
			{
				fclose(fptr);
				printf("Oh no... Could not create file %s\n", fileName);
				printf("Too bad, so sad! Aborting...\n");
				return 0;
			}
			
			for(uint8_t ii=0; ii<strlen(argv[2]) && ii<9; ii++)
			{
				appvarName[ii] = argv[2][ii];
			}
			
			task = CONVERT_FILE;
			break;
		}
		
		task = NONE;
	}
	
	if(task == NONE)
	{
		printf("arg error: %s\n", argv[1]);
		printf(argString);
		printf("Aborting...\n");
		return 0;
	}
	
	if(task == CONVERT_FILE)
	{
		appvar.size = findSize(fileName);
		appvar.data = malloc(appvar.size);
		fread(appvar.data, appvar.size, 1, fptr);
		
		appvar_write(&appvar, fptr);
	}
	
	
	
	return 0;
}

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
		printf("Too much data for AppVar \'%s\'.\n", a->name);
			return -1;
	}
	
	file_size = a->size + APPVAR_DATA_POS + APPVAR_CHECKSUM_LEN;
	data_size = a->size + APPVAR_VAR_HEADER_LEN + APPVAR_VARB_SIZE_LEN;
	var_size  = a->size + APPVAR_VARB_SIZE_LEN;
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

long int findSize(char *file_name)
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");
  
    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    long int res = ftell(fp);
  
    // closing the file
    fclose(fp);
  
    return res;
}
