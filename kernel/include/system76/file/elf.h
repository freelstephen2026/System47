#ifndef _FILE_ELF_H
#define _FILE_ELF_H

#include <types.h>

/* ELF header */
#define E_TYPE
#define E_ENTRY
#define E_PHOFF
#define E_SHOFF
#define E_EHSIZE
#define E_PHENTSIZE
#define E_PHNUM
#define E_SHENTSIZE
#define E_SHNUM
#define E_SHSRNDX

#define ELFCLASS64	1
#define ELFDATA2LSB	1
#define EV_CURRENT	1
#define ET_EXEC		2
#define EM_X86_64	4

//program header table
#define PT_LOAD	1
#define PF_R	0x4
#define PF_X	0x1

#define EXECUTABLE	0
#define TXT 		1
#define COMPRESSED	2

/* this struct still needs some work */
struct elf__LittleEndian
{
	struct elf_header
	{
		struct e_ident
		{
			uint32l EI_MAG;
			uint8l EI_CLASS;
			uint8l EI_DATA;
			uint32l EI_VERSION;
		} e_ident;

		uint16l e_type;
		uint16l e_machine;
		uint32l e_version;
		uint32l e_entry; //memory address where execution starts. aka "entry point"
		uint32l e_phoff; //program header's offset
		uint32l e_shoff;
		uint16l e_ehsize; // elf header's size
		uint16l e_phentsize; // size of a single program header
		uint16l e_phnum; // number of program headers
		uint16l e_shentsize; //size of a single section header
		uint16l e_shnum; // number of section headers
		uint16l e_shstrndx; // index of the name's section in the table
	} elf_header;
	struct prog_header_tbl // program header table
	{
		uint32l p_type;
		uint32l p_offset;
		uint32l p_vaddr;
		uint32l p_paddr;
		uint32l p_filesz;
		uint32l p_memsz;
		uint32l p_flags;
	} prog_header_tbl;
};

struct elf__BigEndian
{
	struct BigEndian__elf_header
	{
		struct BigEndian__e_ident
		{
            uint32b EI_MAG;
            uint8b EI_CLASS;
            uint8b EI_DATA;
            uint32b EI_VERSION
		} e_ident;

        uint16b e_type;
		uint16b e_machine;
		uint32b e_version;
		uint32b e_entry; //memory address where execution starts. aka "entry point"
		uint32b e_phoff; //program header's offset
		uint32b e_shoff;
		uint16b e_ehsize; // elf header's size
		uint16b e_phentsize; // size of a single program header
		uint16b e_phnum; // number of program headers
		uint16b e_shentsize; //size of a single section header
		uint16b e_shnum; // number of section headers
		uint16b e_shstrndx; // index of the name's section in the table
	} elf_header;
	struct BigEndian_prog_header_tbl // program header table
	{
		uint32b p_type;
		uint32b p_offset;
		uint32b p_vaddr;
		uint32b p_paddr;
		uint32b p_filesz;
		uint32b p_memsz;
		uint32b p_flags;
	} prog_header_tbl;
};

#ifdef LITTLE_ENDIAN
#define elf elf__LittleEndian
#endif /* LITTLE_ENDIAN */

#ifdef BIG_ENDIAN
#define elf elf__BigEndian
#endif

#endif /* _FILE_ELF_H */