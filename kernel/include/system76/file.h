/*note - the file system for System47 is FAT*/

#ifndef _FILE_H
#define _FILE_H

#include <types.h>
#include <file/elf.h>

#define EXECUTABLE 	0
#define TXT		1
#define COMPRESSED	2

#define DISKFILE	0
#define STREAMFILE	1
#define DEVICEFILE	2

#define STDIN_HDL	0	/* stdin  file handle */
#define STDOUT_HDL	1  	/* stdout file handle */
#define STDERR_HDL	2	/* stderr file handle */

struct file
{
	ftype type;
	void* data;
};

struct diskFile
{
#ifdef BITS64
	int64 index; /* the position of the file on the file table */
	int64 startingSector;
	int64 endingSector;
#endif /* 64BIT */
	int16 byteEnd; /* the byte offset from the first byte of the ending sector which the file ends */
};

#endif /* _FILE_H */