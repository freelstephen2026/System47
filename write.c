#include <stdio.h>
#include <stdlib.h>

void writeChar(FILE* fp, unsigned char byte)
{
    fputc(byte, fp);
}
#define write(x) writeChar(fp, x)

int main()
{
    FILE* fp = fopen("f.elf", "w");

    write(0x7f); write(0x45); write(0x4c); write(0x46);
    write(0x1);
    write(0x1);
    write(0x1); write(0x0); write(0x0); write(0x0);
    write(0x0); write(0x0); write(0x0); write(0x0); write(0x0); write(0x0);

    write(0x2); write(0x0);
    write(0x28); write(0x0);
}