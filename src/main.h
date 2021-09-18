#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define argString "Args:\n-n <path_to_file>\n"

#define APPVAR_MAX_FILE_SIZE (64 * 1024 + 300)
#define APPVAR_MAX_DATA_SIZE (65505)
#define APPVAR_MAX_BEFORE_COMPRESSION_SIZE (65505*4)

#define APPVAR_TYPE_FLAG 21
#define APPVAR_ARCHIVE_FLAG 128

#define APPVAR_CHECKSUM_LEN 2
#define APPVAR_VARB_SIZE_LEN 2
#define APPVAR_VAR_HEADER_LEN 17
#define APPVAR_FILE_HEADER_LEN 55

#define APPVAR_FILE_HEADER_POS 0x00
#define APPVAR_DATA_SIZE_POS 0x35
#define APPVAR_VAR_HEADER_POS 0x37
#define APPVAR_VAR_SIZE0_POS 0x39
#define APPVAR_TYPE_POS 0x3b
#define APPVAR_NAME_POS 0x3c
#define APPVAR_ARCHIVE_POS 0x45
#define APPVAR_VAR_SIZE1_POS 0x46
#define APPVAR_VARB_SIZE_POS 0x48
#define APPVAR_DATA_POS 0x4a

#define APPVAR_MAGIC 0x0d


struct appvar {
	char name[9];
	int size;
	uint8_t *data;
	int data_len;
	char comment[11];
	uint16_t checkSum;
};

#endif