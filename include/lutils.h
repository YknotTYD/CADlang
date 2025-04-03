/*
** EPITECH PROJECT, 2024
** MY_H
** File description:
** Header file for all.
*/

#ifndef LISTS_H

    #define LISTS_H

    #include <stdlib.h>
    #include <unistd.h>

typedef struct node_s {
    void *data;
    struct node_s *previous;
    struct node_s *next;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
} list_t;

typedef struct {
    list_t *(*new_list)(void);
    node_t *(*append)(list_t *list, void *data);
    node_t *(*pop)(list_t *list, node_t *node);
    node_t *(*pop_index)(list_t *list, int index);
    void (*swap_nodes_data)(node_t *n0, node_t *n1);
    void (*sort)(list_t *list, int (*cmp_func)(void *, void *),
        int is_ascending);
    void (*free_list)(list_t *list);
} lutils_t;

extern const lutils_t lutils;

#endif
