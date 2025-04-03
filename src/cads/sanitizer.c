/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** main.c;
*/

#include "../../include/main.h"

static void remove_comments_sub(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == COMMENT_CHAR) {
            line[i] = '\0';
            return;
        }
    }
    return;
}

void remove_comments(char **file)
{
    for (int i = 0; file[i]; i++) {
        remove_comments_sub(file[i]);
    }
    return;
}

void sanitize(char **file)
{
    char **warray;
    int len;

    remove_comments(file);
    for (int i = 0; file[i]; i++) {
        warray = str_to_warray(file[i], &len, " \t\n,");
        if (warray[0] == 0 || warray[0][0] == '\0') {
            warray_remove_str(file, i);
            i--;
        }
        free_warray(warray);
    }
    return;
}
