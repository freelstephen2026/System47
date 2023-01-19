#include <stdio.h>
#include <types.h>
#include <stdlib.h>

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

int main()
{
    FILE* fp = fopen("f.elf", "r");
    uint16l n = get_uint16l(fp);
	printf("0x%x\n", n);
}