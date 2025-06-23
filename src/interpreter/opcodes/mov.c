/*
** EPITECH PROJECT, 2025
** CADlang
** File description:
** mov.c;
*/

#include "../../../include/main.h"

static int op_mov_rr(cadlangvm_t *vm, reg_t *reg0, reg_t *reg1, void *unused)
{
    (void)unused;
    (void)vm;
    (*reg0) = (*reg1);
    return 0;
}

static int op_mov_rm(cadlangvm_t *vm, reg_t *reg, int *address, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE((*address), sizeof(reg_t)) == 0) {
        return 1;
    }
    my_memcpy(
        reg,
        MEMSPACE_ADDRESS(vm, address),
        sizeof(reg_t)
    );
    return 0;
}

static int op_mov_rd(cadlangvm_t *vm, reg_t *reg, int *value, void *unused)
{
    (void)unused;
    (void)vm;
    (*reg) = (*value);
    return 0;
}

static int op_mov_mr(cadlangvm_t *vm, int *address, reg_t *reg, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE((*address), sizeof(reg_t)) == 0) {
        return 1;
    }
    my_memcpy(
        MEMSPACE_ADDRESS(vm, address),
        reg,
        sizeof(reg_t)
    );
    return 0;
}

static int op_mov_mm(cadlangvm_t *vm, int *address0, int *address1, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE((*address0), INT_SIZE) == 0) {
        return 1;
    }
    if (IS_VALID_MEMORY_SPACE_RANGE((*address1), INT_SIZE) == 0) {
        return 1;
    }
    my_memcpy(
        MEMSPACE_ADDRESS(vm, address0),
        MEMSPACE_ADDRESS(vm, address0),
        INT_SIZE
    );
    return 0;
}

static int op_mov_md(cadlangvm_t *vm, int *address, int *value, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE((*address), INT_SIZE) == 0) {
        return 1;
    }
    my_memcpy(
        MEMSPACE_ADDRESS(vm, address),
        value,
        INT_SIZE
    );
    return 0;
}

op_func load_exec_data(exec_data_t *exec_data, instruction_t *instruction)
{
    (void)exec_data;
    (void)instruction;
    return 0;
}
