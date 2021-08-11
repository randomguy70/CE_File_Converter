#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define FAILED_EXIT_STRING  "[Terminating]"
#define SUCCESS_EXIT_STRING "[Success]\n"

#define DATA_SECTION_OFFSET 55

/* args
name of file to create
string to put inside of file (optional)
*/

/* file format
	http://merthsoft.com/linkguide/ti83+/fformat.html
*/

void createFile(const char *name);
void writeHeader(FILE *filePointer);
void writeDataSection(FILE *filePointer);

int main(int argc, char *argv[]) {
	
	/*
	if(argc < 1) {
		printf("No file found\n");
		printf(FAILED_EXIT_STRING);
		return 0;
	}
	*/
	
	// add .8xv to the end of the file's name
	char newFileName[50];
	strcpy(newFileName, argv[1]);
	strcpy(newFileName+strlen(argv[1]), ".8xv");
	
	createFile(newFileName);
	
	printf("%s %s %s", "File", newFileName, "created.\n");
	printf(SUCCESS_EXIT_STRING);
	
	return 1;
	
}

void createFile(const char *name)
{
	FILE *filePointer = fopen(name, "w+");
	
	writeHeader(filePointer);
	writeDataSection(filePointer);
	
	fclose(filePointer);
	
	return;
}

void writeHeader(FILE *filePointer)
{
	const char *fileComment = "Created by RandomGuy's file converter   ";
	
	fwrite("**TI83F*\x1A\x0A", 11, 1, filePointer);
	fwrite(fileComment, 42, 1, filePointer);
	
	return;
}

void writeDataSection(FILE *filePointer)
{
	uint16_t num = 11;
	uint16_t dataLen = 10;
	char variableTypeID = 0x15;
	
	fseek(filePointer, DATA_SECTION_OFFSET, SEEK_SET);
	fwrite(&num, 2, 1, filePointer);
	fwrite(&dataLen, 2, 1, filePointer);
	fwrite(&variableTypeID, 1, 1, filePointer);
	fwrite("MainData", 8, 1, filePointer);
	
	
	return;
}