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

int main(int argc, char *argv[]) {
	/* arg loop counter */
	size_t i = 0;
	
	enum task task;
	bool convertedFile = false;
	
	for(i = 1; i<argc; i++)
	{
		if(argv[i][0] == '-' && argv[i][1] == 'n')
		{
			task = CONVERT_FILE;
			break;
		}
		task = NONE;
	}
	
	if(task == NONE)
	{
		printf("arg error: ", argv[1], "\n");
		printf(argString);
		return 0;
	}
	
	
	return 0;
}

/*
void createFile(const char *name)
{
	FILE *filePointer = fopen(name, "w+");
	int checkSum;
	uint16_t shortCheckSum;
	
	// we only need the 16 least significant bytes of the int
	shortCheckSum = (uint16_t) checkSum;
	fwrite(&shortCheckSum, 2, 1, filePointer);
	
	fclose(filePointer);
	
	return;
}
*/