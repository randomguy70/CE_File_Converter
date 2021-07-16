#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#ifndef FILE_H
#define FILE_H

struct startingFiles {
	DIR *d; // directory containing files
  	struct dirent *dir; // 
	  
	int numFiles;
	FILE * filePointers[30];
	char fileNames[30][10];
	int fileSizes[30];
};

struct completedFiles {
	int numFiles;
	FILE * filePointers[30];
	char fileNames[30][10];
};

// gets the info about how many text files there are to be converted and necessary data about them, such as their pointers, names, and sizes
void loadFiles(struct startingFiles * starting);

#endif