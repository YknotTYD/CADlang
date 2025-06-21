/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** main.h;
*/

#ifndef CADLANG_MAIN_H

    #define CADLANG_MAIN_H

    typedef struct cads_context_s cads_context_t;

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "vm.h"
    #include "cads_to_cadbin.h"

    #define ERRMSG_FILERR "Coulnd't read file '%s'.\n"
    #define ERRMSG_NEARGS "Not enough arguments given.\n"

    #define CATASTROPHIC_FAILURE (exit(5028841), 5028841)

typedef struct cads_context_s{
    list_t *labels;
    list_t *opcodes;
    char ***file;
    int lone_label_count;
} cads_context_t;

#endif
