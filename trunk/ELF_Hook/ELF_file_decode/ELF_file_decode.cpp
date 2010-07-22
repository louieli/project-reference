// ELF_file_decode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "elf_types.h"
#include "headers.h"
#include "utils.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *file;

	fstream fs;

	//fs.open("proc", std::ios::in | std::ios::binary);
	//fs.open("libc-2.5.so", std::ios::in | std::ios::binary);
	fs.open("ld-2.5.so", std::ios::in | std::ios::binary);

	if(!fs.is_open())
	{
		printf("File \'%s\' cannot be opened.\n", "proc");
		return -1;
	}

	Elf64_Ehdr *e_hdr_ptr = new Elf64_Ehdr;
	Elf64_Phdr *p_hdr_ptr = new Elf64_Phdr;
	Elf64_Shdr *s_hdr_ptr = new Elf64_Shdr;
	Elf64_Sym *sym_ptr = new Elf64_Sym;

	Elf64_Off SymTblFileOffset;
	int SymTblNum;

	Elf64_Off SymNamStrTblFileOffset;
	Elf64_Xword SymNamStrTblSize;

	char *SymNamStrTable;

	char *sec_name_str_table;

	// ------------ Part I: ELF header ------------ //
	// Read program file header.
	if((file = fopen("elf_header.txt", "w")) == NULL)
	{
		printf("File cannot be opened: elf_header.txt\n");
		return -1;
	}
	fs.read((char *)e_hdr_ptr, sizeof(Elf64_Ehdr));
	print_elf_header(e_hdr_ptr, file);
	fclose(file);

	// printf("%lf\n", -1.0 * (e_hdr_ptr->e_phoff - e_hdr_ptr->e_shoff) / sizeof(Elf64_Phdr));
	
	// ------------ Part II: Program header ------------ //
	if((file = fopen("program_header.txt", "w")) == NULL)
	{
		printf("File cannot be opened: program_header.txt\n");
		return -1;
	}

	fs.seekg(e_hdr_ptr->e_phoff, ios::beg);
	for(int i = 0;i<e_hdr_ptr->e_phnum;i++)
	{
		printf("## index: %d\n", i);
		fs.read((char *)p_hdr_ptr, e_hdr_ptr->e_phentsize);
		print_program_header(p_hdr_ptr, file);
	}

	fclose(file);

	// ------------ Part III: Section header table ------------ //
	if((file = fopen("section_header.txt", "w")) == NULL)
	{
		printf("File cannot be opened: section_header.txt\n");
		return -1;
	}

	fs.seekg(e_hdr_ptr->e_shoff + e_hdr_ptr->e_shstrndx * sizeof(Elf64_Shdr), ios::beg);
	// Read information about "Section Name String Table"
	fs.read((char *)s_hdr_ptr, e_hdr_ptr->e_shentsize);
	//printf("*** Section Name String Table File Offset: %d ***\n", s_hdr_ptr->sh_offset);
	//printf("*** Section Name String Table size: %d ***\n", s_hdr_ptr->sh_size);
	fs.seekg(s_hdr_ptr->sh_offset, ios::beg);
	// Read in "Section Name String Table".
	sec_name_str_table = new char[s_hdr_ptr->sh_size + 1];
	fs.read(sec_name_str_table, s_hdr_ptr->sh_size);


	fs.seekg(e_hdr_ptr->e_shoff, ios::beg);	
	for(int i = 0;i<e_hdr_ptr->e_shnum;i++)
	{
		fs.read((char *)s_hdr_ptr, e_hdr_ptr->e_shentsize);

		//if ( strcmp(SecNameStrTable s_hdr_ptr->sh_name, ".symtab") == 0 ) 
		//{
		//	DebugInfoFileOffset = s_hdr_ptr->sh_offset;
		//	DebugInfoSymTblNum = ((s_hdr_ptr->sh_size)/(s_hdr_ptr->sh_entsize));
		//}
		//if ( strcmp(SecNameStrTable s_hdr_ptr->sh_name, ".strtab") == 0 ) 
		//{
		//	DebugInfoStrTblFileOffset = s_hdr_ptr->sh_offset;
		//	DebugInfoStrTblSize = s_hdr_ptr->sh_size;
		//}
		if ( strcmp(sec_name_str_table + s_hdr_ptr->sh_name, ".dynsym") == 0 ) 
		{
			SymTblFileOffset = s_hdr_ptr->sh_offset;
			SymTblNum = (s_hdr_ptr->sh_size)/(s_hdr_ptr->sh_entsize);
		}
		if ( strcmp(sec_name_str_table + s_hdr_ptr->sh_name, ".dynstr") == 0 ) 
		{
			SymNamStrTblFileOffset = s_hdr_ptr->sh_offset;
			SymNamStrTblSize = s_hdr_ptr->sh_size;
		}
		//if ( strcmp(SecNameStrTable s_hdr_ptr->sh_name, ".hash") == 0 ) 
		//{
		//	HashOffset = s_hdr_ptr->sh_offset;
		//	HashTblNum = ((s_hdr_ptr->sh_size)/(s_hdr_ptr->sh_entsize));
		//}
	}

	fs.seekg(e_hdr_ptr->e_shoff, ios::beg);	
	for(int i = 0;i<e_hdr_ptr->e_shnum;i++)
	{
		fs.read((char *)s_hdr_ptr, e_hdr_ptr->e_shentsize);
		print_section_header(s_hdr_ptr, sec_name_str_table, s_hdr_ptr->sh_size, file);
	}

	fclose(file);

	// ------------ Part IV: Symbol Name String Table ------------ //
	if((file = fopen("sym_table.txt", "w")) == NULL)
	{
		printf("File cannot be opened: section_header.txt\n");
		return -1;
	}

	fs.seekg(SymNamStrTblFileOffset, ios::beg);
	SymNamStrTable = new char[SymNamStrTblSize + 1];
	fs.read(SymNamStrTable, SymNamStrTblSize);
	
	fs.seekg(SymTblFileOffset, ios::beg);

	for(int i = 0;i<SymTblNum;i++)
	{
		fs.read((char *)sym_ptr, sizeof(Elf64_Sym));
		print_sym(sym_ptr, SymNamStrTable, file);
	}

	fclose(file);

	// clearing memory.
	delete e_hdr_ptr;
	delete p_hdr_ptr;
	delete s_hdr_ptr;
	delete sym_ptr;

	delete sec_name_str_table;

	fs.close();
	return 0;
}
