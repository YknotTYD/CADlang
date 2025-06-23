/*
** EPITECH PROJECT, 2025
** CADlang
** File description:
** mov.c;
*/

#include "../../../include/main.h"

static int op_mov_rr(cadlangvm_t *vm, void *reg0, void *reg1, void *unused)
{
    (void)unused;
    (void)vm;
    *((reg_t *)reg0) = *((reg_t *)reg1);
    return 0;
}

static int op_mov_rm(cadlangvm_t *vm, void *reg, void *address, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE(*((int *)address), sizeof(reg_t)) == 0) {
        return 1;
    }
    my_memcpy(
        (reg_t *)reg,
        MEMSPACE_ADDRESS(vm, (int *)address),
        sizeof(reg_t)
    );
    return 0;
}

static int op_mov_rd(cadlangvm_t *vm, void *reg, void *value, void *unused)
{
    (void)unused;
    (void)vm;
    *((reg_t *)reg) = *((int *)value);
    return 0;
}

static int op_mov_mr(cadlangvm_t *vm, void *address, void *reg, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE(*((int *)address), sizeof(reg_t)) == 0) {
        return 1;
    }
    my_memcpy(
        MEMSPACE_ADDRESS(vm, (int *)address),
        (reg_t *)reg,
        sizeof(reg_t)
    );
    return 0;
}

static int op_mov_mm(cadlangvm_t *vm, void *address0, void *address1, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE(*((int *)address0), INT_SIZE) == 0) {
        return 1;
    }
    if (IS_VALID_MEMORY_SPACE_RANGE(*((int *)address1), INT_SIZE) == 0) {
        return 1;
    }
    my_memcpy(
        MEMSPACE_ADDRESS(vm, (int *)address0),
        MEMSPACE_ADDRESS(vm, (int *)address1),
        INT_SIZE
    );
    return 0;
}

static int op_mov_md(cadlangvm_t *vm, void *address, void *value, void *unused)
{
    (void)unused;
    if (IS_VALID_MEMORY_SPACE_RANGE(*((int *)address), INT_SIZE) == 0) {
        return 1;
    }
    my_memcpy(
        MEMSPACE_ADDRESS(vm, (int *)address),
        value,
        INT_SIZE
    );
    return 0;
}

static int op_mov_load_arg(exec_data_t *exec_data,
    instruction_t *instruction, int is_r)
{
    if (instruction->operand_types[1] == OPERAND_REGISTER) {
        if (VALUE_TO_INT(instruction, 1) >= REG_COUNT)
            return 1;
        exec_data->op_func = is_r ? op_mov_rr : op_mov_mr;
        exec_data->arg1 = &exec_data->vm->regs[VALUE_TO_INT(instruction, 1)];
    } else if (instruction->operand_types[1] == OPERAND_INDIRECT) {
        exec_data->op_func = is_r ? op_mov_rm : op_mov_mm;
    } else if (instruction->operand_types[1] == OPERAND_DIRECT) {
        exec_data->op_func = is_r ? op_mov_rd : op_mov_md;
    }
    return 0;
}

int op_mov_load_exec_data(exec_data_t *exec_data,
    instruction_t *instruction)
{
    if (instruction->operand_types[2] != OPERAND_NONE) {
        return CATASTROPHIC_FAILURE;
    }
    exec_data->arg2 = 0;
    if (instruction->operand_types[0] == OPERAND_REGISTER) {
        if (VALUE_TO_INT(instruction, 0) >= REG_COUNT) {
            return CATASTROPHIC_FAILURE;
        }
        exec_data->arg0 = &exec_data->vm->regs[VALUE_TO_INT(instruction, 0)];
        op_mov_load_arg(exec_data, instruction, 1);
        return 0;
    } else if (instruction->operand_types[0] == OPERAND_INDIRECT) {
        op_mov_load_arg(exec_data, instruction, 0);
        return 0;
    }
    return CATASTROPHIC_FAILURE;
}
