/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

//32
void print_header32(char *str, Elf32_Ehdr *elf);
int truc_apoint32(Elf32_Ehdr *elf, Elf32_Shdr sec, size_t k);
void dohexa32(Elf32_Ehdr *elf, Elf32_Shdr sec, size_t k);
void to_print32(Elf32_Ehdr *elf, Elf32_Shdr sec);
void data32(Elf32_Ehdr *elf);

//64
void print_header64(char *str, Elf64_Ehdr *elf);
int truc_apoint64(Elf64_Ehdr *elf, Elf64_Shdr sec, size_t k);
void dohexa64(Elf64_Ehdr *elf, Elf64_Shdr sec, size_t k);
void to_print64(Elf64_Ehdr *elf, Elf64_Shdr sec);
void data64(Elf64_Ehdr *elf);



#endif /* !OBJDUMP_H_ */
