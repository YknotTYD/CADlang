/*
** EPITECH PROJECT, 2024
** NOP
** File description:
** void;
*/

#include "../../include/lutils.h"

static list_t *new_list(void)
{
    list_t *new = malloc(sizeof(list_t));

    if (new == 0) {
        return 0;
    }
    new->head = 0;
    new->tail = 0;
    return new;
}

static node_t *append(list_t *list, void *data)
{
    node_t *new = malloc(sizeof(node_t));

    if (new == 0) {
        return 0;
    }
    if (list->head == 0) {
        list->head = new;
        list->head->next = 0;
        list->head->previous = 0;
        list->head->data = data;
        list->tail = list->head;
        return new;
    }
    list->tail->next = new;
    new->previous = list->tail;
    new->next = 0;
    new->data = data;
    list->tail = new;
    return new;
}

static node_t *pop(list_t *list, node_t *node)
{
    if (list->head == 0) {
        return 0;
    }
    if (node == list->head) {
        list->head = node->next;
    }
    if (node == list->tail) {
        list->tail = node->previous;
    }
    if (node->previous) {
        ((node_t *)(node->previous))->next = node->next;
    }
    if (node->next) {
        ((node_t *)(node->next))->previous = node->previous;
    }
    return node;
}

static node_t *pop_index(list_t *list, int index)
{
    node_t *node = list->head;

    if (node == 0) {
        return 0;
    }
    for (int i = 0; i < index; i++) {
        if (node->next == 0) {
            return 0;
        }
        node = node->next;
    }
    return pop(list, node);
}

static void swap_nodes_data(node_t *n0, node_t *n1)
{
    void *temp;

    if (n0 == n1 || n0 == 0 || n1 == 0)
        return;
    temp = n0->data;
    n0->data = n1->data;
    n1->data = temp;
    return;
}

static void swap_if(node_t *n0, node_t *n1, int (*cmp_func)(void *, void *),
    int is_ascending)
{
    is_ascending = is_ascending ? -1 : 1;
    if (cmp_func(n0->data, n1->data) * is_ascending < 0) {
        swap_nodes_data(n0, n1);
    }
    return;
}

static void sort(list_t *list, int (*cmp_func)(void *, void *),
    int is_ascending)
{
    if (list->head == 0) {
        return;
    }
    for (node_t *current = list->head; current; current = current->next) {
        for (node_t *surrent = current; surrent; surrent = surrent->next) {
            swap_if(current, surrent, cmp_func, is_ascending);
        }
    }
    return;
}

static void free_nodes(node_t *node)
{
    if (node->next) {
        free_nodes(node->next);
    }
    free(node);
    return;
}

static void free_list(list_t *list)
{
    if (list->head) {
        free_nodes(list->head);
    }
    free(list);
    return;
}

static void *search(
    list_t *list, int (*func)(),
    void *arg2, int target)
{
    if (list == 0) {
        return 0;
    }
    for (node_t *current = list->head; current; current = current->next) {
        if (arg2 && (func(current->data, arg2) == target)) {
            return current->data;
        }
        if (arg2) {
            continue;
        }
        if (func(current->data) == target) {
            return current->data;
        }
    }
    return 0;
}

const lutils_t lutils = {
    new_list, append, pop,
    pop_index, swap_nodes_data, sort,
    free_list, search
};
