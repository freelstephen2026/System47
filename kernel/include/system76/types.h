#ifndef _TYPES_H
#define _TYPES_H

//file related
typedef void*         fhandle; // file handle
typedef unsigned char ftype;   // file type (executable, txt, compressed)

typedef char      int8;
typedef short int int16;
typedef int       int32;
typedef long long int64;

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef int                uint32;
typedef unsigned long long uint64;

/* little-endian int types */
typedef int8  int8l;
typedef int16 int16l;
typedef int32 int32l;
typedef int64 int64l;

/* little-endian unsigned int types */
typedef uint8  uint8l;
typedef uint16 uint16l;
typedef uint32 uint32l;
typedef uint64 uint64l;

/* big-endian int types */
typedef int8  int8b;
typedef int16 int16b;
typedef int32 int32b;
typedef int64 int64b;

/* big-endian unsigned int types */
typedef uint8  uint8b;
typedef uint16 uint16b;
typedef uint32 uint32b;
typedef uint64 uint64b;

typedef unsigned char Bool;
#define true    1
#define false   0

#endif