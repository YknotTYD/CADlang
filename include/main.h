/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** main.h;
*/

#ifndef CADLANG_MAIN_H

    #define CADLANG_MAIN_H

    typedef struct cads_context_s cads_context_t;
    typedef struct instruction_s instruction_t;

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fcntl.h>
    #include "cads_to_cadbin.h"
    #include "vm.h"

    #define ERRMSG_FILERR "Couldn't open file '%s'."
    #define ERRMSG_FILERRCREAT "Couldn't open or create file '%s'."
    #define ERRMSG_NEARGS "Not enough arguments given."

    #define CATASTROPHIC_FAILURE (exit(36), 36)
    #define CATASTROPHIC_OVERSIGHT (exit(36))

typedef struct cads_context_s{
    list_t *labels;
    list_t *opcodes;
    char ***file;
    int lone_label_count;
    cadlangvm_t vm;
} cads_context_t;

#endif
