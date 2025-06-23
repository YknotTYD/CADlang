/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** vm.h;
*/

#include "main.h"

#ifndef CADLANG_CADLANG_H

    #define CADLANG_CADLANG_H

    #define STACK_SIZE 4096
    #define HEAP_SIZE 16384
    #define MEMORY_SPACE_SIZE (STACK_SIZE + HEAP_SIZE)
    #define HEAP_INDEX STACK_SIZE
    #define HEAP_BITMAP_SIZE (HEAP_SIZE / 8 + 1)

    #define IS_VALID_STACK_RANGE(start, size) (((start) >= 0) && (((start) + (int)(size) - 1) < HEAP_INDEX))
    #define IS_VALID_HEAP_RANGE(start, size) (((start) >= HEAP_INDEX) && (((start) + (int)(size) - 1) < MEMORY_SPACE_SIZE))
    #define IS_VALID_MEMORY_SPACE_RANGE(start, size) (IS_VALID_STACK_RANGE(start, size) || IS_VALID_HEAP_RANGE(start, size))

    #define MEMSPACE_ADDRESS(vm, address) (&(vm)->memory_space[(*(address))])

    #define REG_COUNT 16

typedef int reg_t;
typedef struct cadlangvm_s cadlangvm_t;
typedef int (*op_func_p_t)(cadlangvm_t *vm, void *arg0, void *arg1, void *arg2);

typedef struct {
    op_func_p_t op_func;
    cadlangvm_t *vm;
    void *arg0;
    void *arg1;
    void *arg2;
    int iid;
} exec_data_t;

typedef int (*data_loader_p_t)(exec_data_t *exec_data, instruction_t *instruction);

typedef struct cadlangvm_s {
    unsigned char memory_space[STACK_SIZE + HEAP_SIZE];
    unsigned char heap_bitmap[HEAP_BITMAP_SIZE];
    reg_t regs[REG_COUNT];
    exec_data_t *instructions;
    int sp;
    int pc;
    int clock;
} cadlangvm_t;


int op_mov_load_exec_data(exec_data_t *exec_data, instruction_t *instruction);
int load_vm(cads_context_t *context, char *filepath);

#endif


