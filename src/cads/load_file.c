/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** load_file.c;
*/

#include "../../include/main.h"

/*
for (int aqua0 = 0; (www)[aqua0]; aqua0) {
    for (int aqua1 = 0; ((www)[aqua0])[aqua1]; aqua1) {
        printf("'%s' ", ((www)[aqua0])[aqua1]);
    }
    printf("\n");
}
*/

/*
for (int aqua0 = 0; (www)[aqua0]; aqua0++) {
    printf("'%s' ", (www)[aqua0]);
}
printf("\n");
*/
//for (int aqua0 = 0; (www)[aqua0]; aqua0++){
//printf("'%s' ", (www)[aqua0]);}printf("\n");

void free_cads_context(cads_context_t *cads_context)
{
    for (int i = 0; cads_context->file[i]; i++) {
        free_warray(cads_context->file[i]);
    }
    free(cads_context->file);
    free_labels(cads_context);
    return;
}

static void remove_labels(char ***file)
{
    for (int i = 0; file[i]; i++) {
        if (file[i] == 0 || IS_LABEL(file[i])) {
            free(file[i][0]);
            file[i][0] = 0;
            warray_remove_str((char **)file, i);
            i--;
            continue;
        }
        if (file[i][0][0] == '.' && file[i][1]) {
            warray_remove_str(file[i], 0);
        }
    }
    return;
}

int load_file(cads_context_t *cads_context, char **file)
{
    char **warray;
    int len;

    for (len = 0; file[len]; len++);
    cads_context->file = malloc(sizeof(char **) * (len + 1));
    for (int i = 0; file[i]; i++) {
        warray = str_to_warray(file[i], (int[]){0}, " \t,\n");
        cads_context->file[i] = warray;
        cads_context->file[i + 1] = 0;
    }
    remove_labels(cads_context->file);
    for (int i = 0; cads_context->file[i]; i++) {
        for (int aqua0 = 0; (cads_context->file[i])[aqua0]; aqua0++) {
            printf("'%s' ", (cads_context->file[i])[aqua0]);
        }
        printf("\n");
    }
    return 0;
}
