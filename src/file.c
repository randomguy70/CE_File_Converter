#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include <file.h>
#include <main.h>

void loadFiles(struct startingFiles * starting) {
	DIR * d;
   struct dirent * dir;
	d = opendir(DIRECTORY);
	
	int i = 0;
	if (d) {
		while((dir = readdir(d)) != NULL) {
			
			// if it's an actual file...
			if (dir->d_type == DT_REG) {
			
				strcpy(starting->fileNames[i], dir->d_name);
				starting->filePointers[i] = fopen(dir->d_name, "r+");
  			}
			
			i++;  
		}
	}
}

void writeHeaders() {
	
}

int getSize(FILE * fp) {
	int sz;
	
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	
	return sz;
}