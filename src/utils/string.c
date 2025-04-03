/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** labels.c;
*/

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
