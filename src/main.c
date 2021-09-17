#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define DATA_SECTION_OFFSET 55

/* args
-n <name of file to convert>
string to put inside of file (optional)
*/

/* file format
	http://merthsoft.com/linkguide/ti83+/fformat.html
*/

int main(int argc, char *argv[]) {
	while(int i=0; i<argc; i++) {
		
	}
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
