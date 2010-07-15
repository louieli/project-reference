#include "stdafx.h"

#include "headers.h"

using namespace std;

Elf64_Ehdr *get_elf_header(Elf64_Ehdr *e_hdr_ptr, fstream fs)
{
	if(e_hdr_ptr == NULL)
	{
		return NULL;
	}

	fs.seekg(0);
	fs.read((char *)e_hdr_ptr, sizeof(Elf64_Ehdr));

	return e_hdr_ptr;
}

Elf64_Phdr *get_elf_program_table(Elf64_Phdr *p_hdr_ptr, fstream fs, int count, Elf64_Ehdr *e_hdr_ptr)
{
	if(p_hdr_ptr == NULL)
	{
		return NULL;
	}

	if(e_hdr_ptr == NULL)
	{
		e_hdr_ptr = new Elf64_Ehdr;
		fs.read((char *)e_hdr_ptr, sizeof(Elf64_Ehdr));
	}

	fs.seekg(e_hdr_ptr->e_phoff, ios::beg);

	if(count <= 0)
	{
		count = e_hdr_ptr->e_phnum;
	}

	count = count < e_hdr_ptr->e_phnum ? count : e_hdr_ptr->e_phnum;

	fs.seekg(e_hdr_ptr->e_phoff, ios::beg);
	fs.read((char *)p_hdr_ptr, e_hdr_ptr->e_phentsize * count);
	
	delete e_hdr_ptr;

	return p_hdr_ptr;
}

Elf64_Shdr *get_elf_section_table(Elf64_Shdr *s_hdr_ptr, fstream fs, int count, Elf64_Ehdr *e_hdr_ptr)
{
	if(s_hdr_ptr == NULL)
	{
		return NULL;
	}
	
	if(e_hdr_ptr == NULL)
	{
		e_hdr_ptr = new Elf64_Ehdr;
		fs.read((char *)e_hdr_ptr, sizeof(Elf64_Ehdr));
	}

	if(count <= 0)
	{
		count = e_hdr_ptr->e_shnum;
	}

	count = count < e_hdr_ptr->e_shnum ? count : e_hdr_ptr->e_shnum;

	fs.seekg(e_hdr_ptr->e_shoff + e_hdr_ptr->e_shstrndx * sizeof(Elf64_Shdr), ios::beg);
	fs.read((char *)s_hdr_ptr, e_hdr_ptr->e_shentsize * count);

	delete e_hdr_ptr;

	return s_hdr_ptr;
}

Elf64_Sym *get_elf_sym_table(Elf64_Sym *sym_ptr, fstream fs, int count, Elf64_Ehdr *e_hdr_ptr)
{
	return NULL;
}

Elf64_Off get_sym_table_attrib(fstream fs, Elf64_Ehdr *e_hdr_ptr)
{
	return 0;
}