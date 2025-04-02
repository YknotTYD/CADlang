/*
** EPITECH PROJECT, 2024
** NOP
** File description:
** void;
*/

#include "../../include/main.h"

//add array flags (%S, %I etc...);

static int is_in(char c, char *chars)
{
    for (int i = 0; chars[i]; i++) {
        if (chars[i] == c) {
            return 1;
        }
    }
    return 0;
}

static char *stwa_str_dup(char *str)
{
    int len;
    char *new = 0;

    for (len = 0; str[len]; len++);
    new = malloc(len + 1);
    if (new == 0) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        new[i] = str[i];
    }
    new[len] = 0;
    return new;
}

static int get_word_array_size(char *str, char *seps)
{
    int count = (!is_in(str[0], seps));

    for (int i = 0; str[i + 1]; i++) {
        if (!is_in(str[i], seps)) {
            continue;
        }
        if (!is_in(str[i + 1], seps)) {
            count++;
        }
    }
    return count;
}

static char *copy_word(char **warray, char *str, int index, char *seps)
{
    int lenght;

    for (lenght = 0; str[lenght] && !is_in(str[lenght], seps); lenght++);
    warray[index] = malloc(lenght + 1);
    if (warray[index] == 0) {
        return 0;
    }
    warray[index][lenght] = '\0';
    for (int i = 0; i < lenght; i++) {
        warray[index][i] = str[i];
    }
    return warray[index];
}

static int copy_word_array(char *str, char **warray, char *seps)
{
    int index = 0;

    if (!is_in(str[0], seps)) {
        if (copy_word(warray, str, 0, seps) == 0)
            return 0;
        index++;
    }
    for (int i = 0; str[i + 1]; i++) {
        if (!is_in(str[i], seps)) {
            continue;
        }
        if (is_in(str[i + 1], seps)) {
            continue;
        }
        if (copy_word(warray, &str[i + 1], index, seps) == 0) {
            return 0;
        }
        index++;
    }
    return 1;
}

char **str_to_warray(char *str, int *warray_len, char *seps)
{
    char **warray;

    *warray_len = get_word_array_size(str, seps);
    warray = malloc(sizeof(char *) * (*warray_len + 1));
    if (warray == 0) {
        return 0;
    }
    if (copy_word_array(str, warray, seps) == 0) {
        return 0;
    }
    warray[*warray_len] = 0;
    return warray;
}

char **warray_dup(char **warray)
{
    int len;
    char **new;

    for (len = 0; warray[len]; len++);
    new = malloc(sizeof(char *) * (len + 1));
    if (new == 0) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        new[i] = stwa_str_dup(warray[i]);
        if (new[i] == 0) {
            return 0;
        }
    }
    new[len] = 0;
    return new;
}

void free_warray(char **warray)
{
    for (int i = 0; warray[i]; i++) {
        free(warray[i]);
    }
    free(warray);
    return;
}
