#include "stdafx.h"

#include "headers.h"
#include "utils.h"

void print_elf_header(Elf64_Ehdr *e_hdr_ptr, FILE *file)
{
	FILE *f = file;
	if(f == NULL)
	{
		f = stdout;
	}

	fprintf(f, "------------------------------ ELF header start -------------------------------\r\n");
	fprintf(f, "(Magic number and other info)e_ident: %s\r\r\n", e_hdr_ptr->e_ident);
	fprintf(f, "(Object file type)e_type: 0x%02x\r\n",e_hdr_ptr->e_type);
	fprintf(f, "(Architecture)e_machine: 0x%02x\r\n",e_hdr_ptr->e_machine);
	fprintf(f, "(Object file version)e_version: 0x%02x\r\n",e_hdr_ptr->e_version);
	fprintf(f, "(Entry point virtual address)e_entry: 0x%02x\r\n",e_hdr_ptr->e_entry);
	fprintf(f, "(Program header table file offset)e_phoff: 0x%02x\r\n",e_hdr_ptr->e_phoff);
	fprintf(f, "(Section header table file offset)e_shoff: 0x%02x\r\n",e_hdr_ptr->e_shoff);
	fprintf(f, "(Processor-specific flags)e_flags: 0x%02x\r\n",e_hdr_ptr->e_flags);
	fprintf(f, "(ELF header size in bytes)e_ehsize: 0x%02x = %d\r\n",e_hdr_ptr->e_ehsize, e_hdr_ptr->e_ehsize);
	fprintf(f, "(Program header table entry size)e_phentsize: 0x%02x = %d\r\n",e_hdr_ptr->e_phentsize, e_hdr_ptr->e_phentsize);
	fprintf(f, "(Program header table entry count)e_phnum: 0x%02x = %d\r\n",e_hdr_ptr->e_phnum, e_hdr_ptr->e_phnum);
	fprintf(f, "(Section header table entry size)e_shentsize: 0x%02x = %d\r\n",e_hdr_ptr->e_shentsize, e_hdr_ptr->e_shentsize);
	fprintf(f, "(Section header table entry count)e_shnum: 0x%02x = %d\r\n",e_hdr_ptr->e_shnum, e_hdr_ptr->e_shnum);
	fprintf(f, "(Section header string table index)e_shstrndx: 0x%02x = %d\r\n",e_hdr_ptr->e_shstrndx, e_hdr_ptr->e_shstrndx);
	fprintf(f, "------------------------------ ELF header end ---------------------------------\r\n");
}

void print_program_header(Elf64_Phdr *p_hdr_ptr, FILE *file)
{
	FILE *f = file;
	if(f == NULL)
	{
		f = stdout;
	}

	fprintf(f, "---------------------------- Program entry start ------------------------------\r\n");
	fprintf(f, "(Segment type)p_type: 0x%02x\n",	p_hdr_ptr->p_type);
	fprintf(f, "(Segment flags)p_flags: 0x%02x\n",p_hdr_ptr->p_flags);
	fprintf(f, "(Segment file offset)p_offset: 0x%02x\n",	p_hdr_ptr->p_offset);
	fprintf(f, "(Segment virtual address)p_vaddr: 0x%02x\n",p_hdr_ptr->p_vaddr);
	fprintf(f, "(Segment physical address)p_paddr: 0x%02x\n",p_hdr_ptr->p_paddr);
	fprintf(f, "(Segment size in file)p_filesz: 0x%02x\n",p_hdr_ptr->p_filesz);
	fprintf(f, "(Segment size in memory)p_memsz: 0x%02x\n",p_hdr_ptr->p_memsz);
	fprintf(f, "(Segment alignment)p_align: 0x%02x\n",p_hdr_ptr->p_align);
	
	fprintf(f, "---------------------------- Program entry end --------------------------------\r\n");
}

void print_section_header(Elf64_Shdr *s_hdr_ptr, char * sec_name_str_table, Elf64_Xword size, FILE *file)
{
	FILE *f = file;
	if(f == NULL)
	{
		f = stdout;
	}

	fprintf(f, "---------------------------- Section entry start ------------------------------\r\n");
	fprintf(f, "(Section name (string tbl index))sh_name: 0x%02x -> %s\n",
		s_hdr_ptr->sh_name, sec_name_str_table + s_hdr_ptr->sh_name);
	fprintf(f, "(Section type)sh_type: 0x%02x\n",	s_hdr_ptr->sh_type);
	fprintf(f, "(Section flags)sh_flags: 0x%02x\n",s_hdr_ptr->sh_flags);
	fprintf(f, "(Section virtual addr at execution)sh_addr: 0x%02x\n",s_hdr_ptr->sh_addr);
	fprintf(f, "(Section file offset)sh_offset: 0x%02x\n",s_hdr_ptr->sh_offset);
	fprintf(f, "(Section size in bytes)sh_size: 0x%02x\n",s_hdr_ptr->sh_size);
	fprintf(f, "(Link to another section)sh_link: 0x%02x\n",s_hdr_ptr->sh_link);
	fprintf(f, "(Additional section information)sh_info: 0x%02x\n",s_hdr_ptr->sh_info);
	fprintf(f, "(Section alignment)sh_addralign: 0x%02x\n",s_hdr_ptr->sh_addralign);
	fprintf(f, "(Entry size if section holds table)sh_entsize: 0x%02x\n",s_hdr_ptr->sh_entsize);
	fprintf(f, "---------------------------- Section entry end --------------------------------\r\n");
}

void print_sym(Elf64_Sym *sym_ptr, char * SymNamStrTable, FILE *file)
{
	FILE *f = file;
	if(f == NULL)
	{
		f = stdout;
	}

	fprintf(f, "---------------------------- Symbol table start -------------------------------\r\n");
	fprintf(f, "Symbol_index_and_name: 0x%02x -> %s\n",sym_ptr->st_name, SymNamStrTable + sym_ptr->st_name);
	fprintf(f, "Symbol_value: 0x%02x\n", sym_ptr->st_value);
	fprintf(f, "Symbol_size: 0x%02x\n", sym_ptr->st_size);
	fprintf(f, "Symbol_type_and_binding: 0x%02x\n", sym_ptr->st_info);
	fprintf(f, "Section_index: 0x%02x\n", sym_ptr->st_shndx);
	fprintf(f, "---------------------------- Symbol table end ---------------------------------\r\n");
}

unsigned long elf64_hash(const unsigned char *name)
{
	unsigned long h = 0, g;
	while (*name) 
	{
		h = (h << 4) + *name++;
		if (g = h & 0xf0000000)
		h ^= g >> 24;
		h &= 0x0fffffff ;
	}
	return h;
}
