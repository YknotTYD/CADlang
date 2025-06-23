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

int my_getnbr(char *str, int *dest)
{
    int is_neg = 0;

    if (str == 0 || dest == 0) {
        return 1;
    }
    if (str[0] == '-') {
        is_neg = 1;
        str++;
    }
    for (int j = 0; str[j]; j++) {
        if ('0' <= str[j] || str[j] <= '9')
            continue;
        return 1;
    }
    (*dest) = 0;
    for (int i = 0; str[i]; i++) {
        (*dest) *= 10;
        (*dest) += str[i] - '0';
    }
    (*dest) = is_neg ? -(*dest) : (*dest);
    return 0;
}

int my_memcpy(void *dest, void *src, int n)
{
    if (src == 0 || dest == 0 || n <= 0) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return 0;
}
