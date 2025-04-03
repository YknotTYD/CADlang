/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** labels.c;
*/

#include "../../include/main.h"

int my_strcmp(char *str0, char *str1)
{
    int i;

    for (i = 0; str0[i] && str1[i]; i++) {
        if (str0[i] - str1[i]) {
            return str0[i] - str1[i];
        }
    }
    return str0[i] - str1[i];
}

static void copy_lines(char *line, char ***file, FILE *stream)
{
    size_t len = 0;

    for (int i = 0; getline(&line, &len, stream) != -1; i++) {
        (*file) = realloc((*file), sizeof(char *) * (i + 2));
        if ((*file) == 0)
            return;
        (*file)[i] = strdup(line);
        if ((*file)[i] == 0) {
            free((*file));
            return;
        }
        (*file)[i + 1] = 0;
    }
    free(line);
    return;
}

char **read_file(const char *filepath)
{
    char **file = 0;
    char *line = 0;
    FILE *stream = fopen(filepath, "r");

    if (stream == 0)
        return 0;
    copy_lines(line, &file, stream);
    fclose(stream);
    return file;
}
