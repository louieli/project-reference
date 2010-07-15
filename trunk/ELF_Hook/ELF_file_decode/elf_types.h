#pragma once

typedef unsigned __int64 Elf64_Addr;
typedef unsigned __int64 Elf64_Off;
typedef unsigned short Elf64_Half;
typedef unsigned int Elf64_Word;
typedef int Elf64_Sword;
typedef unsigned __int64 Elf64_Xword;
typedef __int64 Elf64_Sxword;

// File identification
#define EI_MAG0 0

#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3

// File class
#define EI_CLASS 4

// Data encoding
#define EI_DATA 5

// File version
#define EI_VERSION 6

// OS/ABI identification
#define EI_OSABI 7

// ABI version
#define EI_ABIVERSION 8

// Start of padding bytes
#define EI_PAD 9

// Size of e_ident[]
#define EI_NIDENT 16
