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
int writeDataSection(FILE *filePointer);

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
	int checkSum;
	uint16_t shortCheckSum;
	
	writeHeader(filePointer);
	checkSum = writeDataSection(filePointer);
	
	// we only need the 16 least significant bytes of the int
	shortCheckSum = (uint16_t) checkSum;
	fwrite(&shortCheckSum, 2, 1, filePointer);
	
	fclose(filePointer);
	
	return;
}

void writeHeader(FILE *filePointer)
{
	const char *fileComment = "Created by RandomGuy's file converter   ";
	
	fseek(filePointer, 0, SEEK_SET);
	fwrite("**TI83F*\x1A\x0A", 11, 1, filePointer);
	fwrite(fileComment, 42, 1, filePointer);
	
	return;
}

int writeDataSection(FILE *filePointer)
{
	uint16_t num = 11;
	uint16_t dataLen = 10;
	char variableTypeID = 0x15;
	uint8_t zero = 0x00;
	uint8_t version = 0;
	uint8_t flag = 0x80; // 80 == archived
	
	int totalDataSize = dataLen + 17;
	int checkSum = 0;
	char checkSumData[totalDataSize]; // the complete content of this variable entry (everything I have written into the file in this function)
	
	fseek(filePointer, DATA_SECTION_OFFSET, SEEK_SET);
	fwrite(&num, 2, 1, filePointer);
	fwrite(&dataLen, 2, 1, filePointer);
	fwrite(&variableTypeID, 1, 1, filePointer);
	fwrite("main", 4, 1, filePointer);
	fwrite(&zero, 1, 4, filePointer);
	fwrite(&version, 1, 1, filePointer);
	fwrite(&flag, 1, 1, filePointer);
	fwrite(&dataLen, 2, 1, filePointer);
	
	// actual data (finally!!!)
	fwrite("Finally!!!", 10, 1, filePointer);
	
	// calculate the checksum of the data variable entry
	fseek(filePointer, DATA_SECTION_OFFSET, SEEK_SET);
	fread(checkSumData, totalDataSize, 1, filePointer);
	
	for(int i=0; i<totalDataSize; i++) {
		checkSum += checkSumData[i];
	}
	
	// be generous to myself and seek to the end of the data section (helpful back in the creating file function)
	fseek(filePointer, DATA_SECTION_OFFSET + totalDataSize, SEEK_SET);
	
	return checkSum;
}