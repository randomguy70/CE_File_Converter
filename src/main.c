#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define FAILED_EXIT_STRING  "[Terminating]"
#define SUCCESS_EXIT_STRING "[Success]\n"

#define DATA_SECTION_OFFSET 57

/* args
name of file to create
string to put inside of file (optional)
*/

/* file format
	http://merthsoft.com/linkguide/ti83+/fformat.html
*/

FILE *createFile(const char *name);
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
	
//	createFile(newFileName);
	
	printf("%s %s %s", "File", newFileName, "created.\n");
	printf(SUCCESS_EXIT_STRING);
	
	return 1;
	
}

FILE *createFile(const char *name)
{
	FILE *filePointer = fopen(name, "w+");
	
	writeHeader(filePointer);
	writeDataSection(filePointer);
	
	return filePointer;
}

void writeHeader(FILE *filePointer)
{
	const char *fileHeader = "**TI83F*";
	unsigned int fileSignature = 0x1A0A00;
	const char *fileComment = "Created by RandomGuy's file converter   ";
	
	fseek(filePointer, 0, SEEK_SET);
	fwrite(fileHeader, strlen(fileHeader), 1, filePointer);
	
	fseek(filePointer, 8, SEEK_SET);
	fwrite(&fileSignature, 3, 1, filePointer);
	
	fseek(filePointer, 11, SEEK_SET);
	fwrite(fileComment, strlen(fileComment), 1, filePointer);
	
	return;
}

void writeDataSection(FILE *filePointer)
{
	fseek(filePointer, DATA_SECTION_OFFSET, SEEK_SET);
	
}