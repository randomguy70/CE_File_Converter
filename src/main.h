#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define argString "Args:\n-n <path_to_file>\n"

#define APPVAR_VAR_HEADER_POS 0x37
#define APPVAR_HEADER_SIZE 11
#define APPVAR_COMMENT_SIZE 42
#define APPVAR_MAX_FILE_SIZE (64 * 1024 + 300)

struct appvar {
	char name[9];
	int size;
	uint8_t *data;
	int data_len;
	char comment[11];
	uint16_t checkSum;
};

#endif