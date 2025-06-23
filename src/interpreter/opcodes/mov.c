/*
** EPITECH PROJECT, 2025
** CADlang
** File description:
** mov.c;
*/

#include "../../../include/main.h"

//REG -> MEM
//REG -> REG
//MEM -> MEM

//R M D
//
//R R
//R M
//R D
//M R
//M M
//M D

static int op_mov_rr(cadlangvm_t *vm, reg_t *reg0, reg_t *reg1)
{
    (void)vm;
    (*reg0) = (*reg1);
    return 0;
}

static int op_mov_rm(cadlangvm_t *vm, reg_t *reg, int *address)
{
    if (IS_VALID_MEMORY_SPACE_RANGE((*address), sizeof(reg_t)) == 0) {
        return 1;
    }
    my_memcpy(reg, MEMSPACE_ADDRESS(vm, address), sizeof(reg_t));
    return 0;
}

static int op_mov_rd(cadlangvm_t *vm, reg_t *reg, int *value)
{
    (void)vm;
    (*reg) = (*value);
    return 0;
}

static int op_mov_mr(cadlangvm_t *vm, int *address, reg_t *reg)
{
    if (IS_VALID_MEMORY_SPACE_RANGE((*address), sizeof(reg_t)) == 0) {
        return 1;
    }
    my_memcpy(MEMSPACE_ADDRESS(vm, address), reg, sizeof(reg_t));
    return 0;
}

static int op_mov_mm(cadlangvm_t *vm, int *address0, int *address1)
{
    if (IS_VALID_MEMORY_SPACE_RANGE((*address0), INT_SIZE) == 0) {
        return 1;
    }
    if (IS_VALID_MEMORY_SPACE_RANGE((*address1), INT_SIZE) == 0) {
        return 1;
    }
    my_memcpy(MEMSPACE_ADDRESS(vm, address0), MEMSPACE_ADDRESS(vm, address0), INT_SIZE);
    return 0;
}
static int op_mov_md(cadlangvm_t *vm, int *address, int *value)
{
    if (IS_VALID_MEMORY_SPACE_RANGE((*address), INT_SIZE) == 0) {
        return 1;
    }
    my_memcpy(MEMSPACE_ADDRESS(vm, address), value, INT_SIZE);
    return 0;
}

