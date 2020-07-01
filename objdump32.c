/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019
** File description:
** objdump
*/

#include "objdump.h"

void print_header32(char *str, Elf32_Ehdr *elf)
{
    printf("\n%s:     file format elf32-i386\n", str);
    printf("architecture: i386, ");
    if (elf->e_type == ET_REL)
        printf("flags 0x00000011:\nHAS_RELOC, HAS_SYMS\n");
    if (elf->e_type == ET_EXEC)
        printf("flags 0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED\n");
    if (elf->e_type == ET_DYN)
        printf("flags 0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
    printf("start address 0x%08x\n\n", elf->e_entry);
}

int truc_apoint32(Elf32_Ehdr *elf, Elf32_Shdr sec, size_t k)
{
    char pute = ((char *)elf + sec.sh_offset)[k];
    if (pute > 32 && pute < 126)
        printf("%c", pute);
    else
        printf(".");
    return (1);
}

void dohexa32(Elf32_Ehdr *elf, Elf32_Shdr sec, size_t k)
{
    for (; k < sec.sh_size ;) {
        char pute = ((char *)elf + sec.sh_offset)[k];
        printf("%02x", (unsigned char)pute);
        k += 1;
        if (k % 16 == 0) {
            printf("  ");
            break;
        } else if (k % 4 == 0)
            printf(" ");
    }
    if (k % 16 != 0) {
        for (k = k + 1 ; (k - 1) % 16 != 0 ; k++) {
            if (k % 16 == 0 || k % 4 == 0)
                printf(" ");
            printf("  ");
        }
        printf(" ");
    }
}

void to_print32(Elf32_Ehdr *elf, Elf32_Shdr sec)
{
    int nb = 0;

    for (size_t j = sec.sh_addr, k = 0 ; k < sec.sh_size ; k++) {
        if (k % 16 == 0) {
            nb = 0;
            printf(" %04x ", j);
            dohexa32(elf, sec, k);
            j += 16;
        }
        nb += truc_apoint32(elf, sec, k);
        if ((k + 1) % 16 == 0)
            printf("\n");
    }
    if (nb < 16) {
        for (; nb < 16 ; nb++)
            printf(" ");
        printf("\n");
    }
}

void data32(Elf32_Ehdr *elf)
{
    Elf32_Shdr *sec = (void *)elf + elf->e_shoff;
    char *stable = (char *)((void *)elf + sec[elf->e_shstrndx].sh_offset);
    char *name = NULL;

    for (int i = 1 ; i < elf->e_shnum ; i++) {
        name = &stable[sec[i].sh_name];
        if (strcmp(name, ".bss") != 0 && strcmp(name, ".symtab") != 0 &&
            strcmp(name, ".strtab") != 0 && strcmp(name, ".shstrtab") != 0) {
            printf("Contents of section %s:\n", name);
            to_print32(elf, sec[i]);
        }
    }
}

