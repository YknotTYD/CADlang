/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** main.c;
*/

#include "../include/main.h"

//put error messages in stderr;
//make str_to_warray take consts;
//get it on snap;
//add a docs site;
//add MOVB
//make error messages red when !isatty;

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

static char **read_file(const char *filepath)
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

int main(void)
{
    char **file = read_file("temp.cads");

    if (file == 0) {
        printf(
            COLOR_ERR"Coulnd't read file '%s'.\n"COLOR_DEFAULT, "temp.cads");
        return 84;
    }
    parse(file);
    for (int i = 0; file[i]; i++) {
        free(file[i]);
    }
    free(file);
    return 0;
}
