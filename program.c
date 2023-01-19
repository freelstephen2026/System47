#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//configs
#include "test-config.h"

//kernel
#include <types.h>
#include <file.h>

//#define WRITE
#define READ

#define HEAP(x,y)	x* ____MACRO_yPtr = malloc(sizeof(x)); y = 

struct elf* getElf(FILE* fp)
{
	struct elf* ret = malloc(sizeof(struct elf));
	char* EI_MAG_str = malloc(sizeof(uint32) * sizeof(char)); /* this is a string of all the bytes that represent all the bytes within `ret->elf_header.e_ident.EI_MAG` */
	fgets(EI_MAG_str, 3, fp);
	printf("%s\n", EI_MAG_str);

	return ret;
}

static Bool sameStrs(char* str1, char* str2)
{
	Bool ret = true;
	if (strlen(str1) != strlen(str2))
		return false;
	else
	{
		for (int i = 0; i < strlen(str1); i++)
		{
			if (str1[i] != str2[i])
			{
				ret = false;
				break;
			}
		}
	}

	return ret;
}

static char* reverseString(char* str)
{
	char* ret = malloc(strlen(str) * sizeof(char));
	for (int i = 0; i < strlen(str); i++)
	{
		ret[i] = str[strlen(str) - i - 1];
	}
	ret[strlen(str)] = '\0';
	return ret;
}

static uint8l get_uint8l(FILE* fp)
{
	char* str = malloc(sizeof(char));
	fgets(str, 2, fp);
	uint8l* retPtr = (uint8l*)str;
	return *retPtr;
}

char* charVals(char* str)
{
	char hexChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    char* ret = malloc((2 + 2 + 6 * strlen(str)) * sizeof(char));
    ret[0] = '{';
    int64 currentRetIndex = 1;
    for (int i = 0; i < strlen(str); i++) {
        ret[currentRetIndex] = '0';
        ret[currentRetIndex + 1] = 'x';
        int val = str[i];
        if (val < 0x10) {
            ret[currentRetIndex + 2] = '0';
        } else {
            ret[currentRetIndex + 2] = hexChars[val / 0x10];
        }
        ret[currentRetIndex + 3] = hexChars[val % 0x10];
        if (i + 1 != strlen(str)) {
            ret[currentRetIndex + 4] = ',';
            ret[currentRetIndex + 5] = ' ';
            currentRetIndex += 6;
        }
        else {
            currentRetIndex += 4;
        }
    }
    ret[currentRetIndex] = '}';
    ret[currentRetIndex + 1] = '\0';
    return ret;
}

static uint16l bytes_get_uint16l(char* bytes)
{
 	uint16l result = bytes[0] & 0xff;
	result |= (bytes[1] & 0xff) << 8;
	return result;
}

static uint16l get_uint16l(FILE* fp)
{
	char* bytes = malloc(2 * sizeof(char));
	fgets(bytes, 3, fp);
	return bytes_get_uint16l(bytes);
}

static uint32l get_uint32l(FILE* fp)
{
	char* str = malloc(4 * sizeof(char));
	fgets(str, 5, fp);
	uint32l* retPtr = (uint32l*)str;
	return *retPtr;
}

static uint32b get_uint32b(FILE* fp)
{
	char* str = malloc(4 * sizeof(char));
	fgets(str, 5, fp);
	uint32b* retPtr = (uint32b*)str;
	return *retPtr;
}

struct elf* get_elf(FILE* fp)
{
	char* firstChar = malloc(sizeof(char));
	fgets(firstChar, 2, fp);
	printf("char1 = %d\n", *firstChar);
	if (*firstChar != 0x7f)
	{
		fprintf(stderr, "warning - FILE* %p's EI_MAG attribute does not exist because the file's first char is not '.'. `get_elf` returning `NULL`-valued pointer.\n", fp);
		return (struct elf*)NULL;
	}

	struct elf* ret = malloc(sizeof(struct elf));
	char* EI_MAG_str = malloc(4 * sizeof(char));
	char* EI_MAG_str_end = malloc(3 * sizeof(char));
	fgets(EI_MAG_str_end, 4, fp);
	EI_MAG_str[0] = '.';
	EI_MAG_str[1] = EI_MAG_str_end[0];
	EI_MAG_str[2] = EI_MAG_str_end[1];
	EI_MAG_str[3] = EI_MAG_str_end[2];
	EI_MAG_str[4] = 0x0;

	int32* EI_MAG_INT32PTR = malloc(sizeof(int32));

#ifdef LITTLE_ENDIAN
	char* EI_MAG_str_reverse = malloc(4 * sizeof(char));
	EI_MAG_str_reverse[0] = EI_MAG_str[3];
	EI_MAG_str_reverse[1] = EI_MAG_str[2];
	EI_MAG_str_reverse[2] = EI_MAG_str[1];
	EI_MAG_str_reverse[3] = EI_MAG_str[0];
	/* this string is only for casting to integer. no null-terminator needed, since we are not printing it. */

	EI_MAG_INT32PTR = (int*)EI_MAG_str_reverse;

	ret->elf_header.e_ident.EI_MAG = *EI_MAG_INT32PTR;
	ret->elf_header.e_ident.EI_CLASS = get_uint8l(fp);
	ret->elf_header.e_ident.EI_DATA = get_uint8l(fp);
	ret->elf_header.e_ident.EI_VERSION = get_uint32l(fp);

	char* unusedStr = malloc(20 * sizeof(char));
	fgets(unusedStr, 7, fp);

	ret->elf_header.e_type = get_uint16l(fp);
	ret->elf_header.e_machine = get_uint16l(fp);
	ret->elf_header.e_version = get_uint32l(fp);
#endif /* LITTLE_ENDIAN */

#ifdef BIG_ENDIAN
	EI_MAG_INT32PTR = (int*)EI_MAG_str;
	ret->elf_header.e_ident.EI_MAG = *EI_MAG_INT32PTR;
#endif /* BIG_ENDIAN */

	ret->elf_header.e_ident.EI_VERSION;

	return ret;
}

void* getNthPtr(void* ptr, uint64 n)
{
	void* k = ptr;
	void* kVal = ptr;
	for (int i = 0; i < n - 1; i++)
	{
		k = malloc(8);
		//*k = kVal;
		k = (void*)(&k);
		//kVal = *k;
	}
	return k;
}

int main2()
{
    int* ptr = malloc(sizeof(int));
    printf("*%p = %d\n", ptr, *ptr);

	FILE* fp = fopen("file.elf", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: fopen(\"file.elf\", \"r\") is a null pointer. Quitting.");
		return 1;
	}

	getElf(fp);

	printf("fp=%c%c%c\n", fgetc(fp), fgetc(fp), fgetc(fp));

	char* s = "\002\003\004\005";
	// 0x2030405
	//printf("%lld\n", (int64)1 << 32);
	printf("%lld\n", (uint64)5 + ((uint64)4 << 8) + ((uint64)3 << 16) + ((uint64)2 << 24));

	printf("%d\n", '\xa'==10);
	fclose(fp);
	return 0;
}

void printData(struct elf File)
{
	printf("{\n");

	printf("\t.e_ident = \n");
	printf("\t{\n");
	printf("\t\t.EI_MAG = 0x%x\n", File.elf_header.e_ident.EI_MAG);
	printf("\t\t.EI_CLASS = 0x%x\n", File.elf_header.e_ident.EI_CLASS);
	printf("\t\t.EI_DATA = 0x%x\n", File.elf_header.e_ident.EI_DATA);
	printf("\t\t.EI_VERSION = 0x%x\n", File.elf_header.e_ident.EI_VERSION);
	printf("\t}\n\n");

	printf("\t.e_type = 0x%x\n", File.elf_header.e_type);

	printf("}\n");
}

int main()
{
#ifdef WRITE
	FILE* fpw = fopen("f.elf", "wb");
	if (fpw == NULL)
	{
		fprintf(stderr, "error opening f.elf with wb\n");
		exit(1);
	}
#endif

#ifdef READ
	FILE* fpr = fopen("f.elf", "rb");
	if (fpr == NULL)
	{
		fprintf(stderr, "error opening f.elf with rb\n");
		exit(1);
	}
	struct elf* data = get_elf(fpr);
	printData(*data);

	char* str = charVals("abcabc");

	printf("%s\n", str);
	printf("%d", str[0]);
#endif
}