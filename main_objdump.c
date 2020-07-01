/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019
** File description:
** main_objdump
*/

#include "objdump.h"

Elf64_Ehdr *openit64(char *str)
{
    int fd;
    void *buf;
    struct stat s;
    Elf64_Ehdr *elf;

    fd = open(str, O_RDONLY);
    if (fd != -1) {
        fstat(fd, &s);
        buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf != -1) {
            elf = buf;
        } else {
            perror("mmap");
        }
        close(fd);
    }
    return (elf);
}

Elf32_Ehdr *openit32(char *str)
{
    int fd;
    void *buf;
    struct stat s;
    Elf32_Ehdr *elf;

    fd = open(str, O_RDONLY);
    if (fd != -1) {
        fstat(fd, &s);
        buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf != -1) {
            elf = buf;
        } else {
            perror("mmap");
        }
        close(fd);
    }
    return (elf);
}

int main(int ac, char **av)
{
    Elf64_Ehdr *elf;
    Elf32_Ehdr *elf32;

    (ac != 2) ? write(2, "No file specified.\n", 20), exit(84): 0;
    elf = openit64(av[1]);
    elf32 = openit32(av[1]);
    if (elf->e_type != ET_REL && elf->e_type != ET_EXEC &&
        elf->e_type != ET_DYN) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", av[1]);
        return (84);
    }
    if (elf->e_ident[EI_CLASS] == ELFCLASS32) {
        print_header32(av[1], elf32);
        data32(elf32);
    } else if (elf->e_ident[EI_CLASS] == ELFCLASS64) {
        print_header64(av[1], elf);
        data64(elf);
    }
    return (0);
}