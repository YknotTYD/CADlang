/*
** EPITECH PROJECT, 2025
** CADlang
** File description:
** vm.c;
*/

#include "../../include/main.h"

static void init_vm(cadlangvm_t *vm)
{
    for (int i = 0; i < MEMORY_SPACE_SIZE; i++)
        vm->memory_space[i] = 0;
    for (int i = 0; i < HEAP_BITMAP_SIZE; i++)
        vm->heap_bitmap[i] = 0;
    for (int i = 0; i < REG_COUNT; i++)
        vm->regs[i] = 0;
    vm->pc = 0;
    vm->sp = 0;
    vm->clock = 0;
    return;
}

static data_loader_p_t data_loaders[INSTRUCTION_COUNT] = {
    op_mov_load_exec_data, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0
};

static void load_exec_data(cadlangvm_t *vm, exec_data_t *exec_data,
    instruction_t *instruction)
{
    if (instruction->iid >= INSTRUCTION_COUNT) {
        CATASTROPHIC_OVERSIGHT;
        return;
    }
    exec_data->vm = vm;
    if (data_loaders[instruction->iid]) {
        data_loaders[instruction->iid](exec_data, instruction);
    }
    return;
}

int load_vm(cads_context_t *context, char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    instruction_t *instructions_data;
    exec_data_t *exec_data;
    int len;

    init_vm(&context->vm);
    if (fd == -1) {
        return CATASTROPHIC_FAILURE;
    }
    len = lseek(fd, 0, SEEK_END) - SHEBANG_LEN;
    lseek(fd, SHEBANG_LEN, SEEK_SET);
    instructions_data = alloca(len);
    read(fd, instructions_data, len);
    close(fd);
    len /= sizeof(instruction_t);
    exec_data = malloc(sizeof(exec_data_t) * len);
    for (int i = 0; i < len; i++) {
        load_exec_data(&context->vm, &exec_data[i], &instructions_data[i]);
    }
    free(exec_data);
    return 0;
}
