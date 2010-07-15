#pragma once

void print_elf_header(Elf64_Ehdr *e_hdr_ptr, FILE *file = NULL);
void print_program_header(Elf64_Phdr *p_hdr_ptr, FILE *file = NULL);
void print_section_header(Elf64_Shdr *s_hdr_ptr, char * sec_name_str_table, Elf64_Xword size, FILE *file = NULL);
void print_sym(Elf64_Sym *sym_ptr, char * SymNamStrTable, FILE *file = NULL);

unsigned long elf64_hash(const unsigned char *name);