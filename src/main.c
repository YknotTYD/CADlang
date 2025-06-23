/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** main.c;
*/

#include "../include/main.h"

//make str_to_warray take consts;
//get it on snap;
//add a docs site;
//add MOVB;
//find a better way than to cast everything to ints
//check for overflows in the ASM

//TODO: add error handling for labels pointing on nothing;

static void __attribute__((__destructor__)) close_std(void)
{
    for (int i = 0; i < 3; i++) {
        close(i);
    }
    return;
}

static int parse_error(cads_context_t *cads_context, char **file)
{
    cads_context->labels = lutils.new_list();
    if (parse_labels(cads_context, file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    if (parse(cads_context->labels, file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    free_labels(cads_context);
    return 0;
}

static int is_duplicate_line(label_t *label, list_t *labels)
{
    for (node_t *current = labels->head; current; current = current->next) {
        if (label != current->data &&
            label->line == ((label_t *)current->data)->line) {
            return 1;
        }
    }
    return 0;
}

static int parse_non_error(cads_context_t *cads_context, char **file)
{
    cads_context->labels = lutils.new_list();
    sanitize(file);
    if (parse_labels(cads_context, file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    for (node_t *current = cads_context->labels->head; current;
        current = current->next) {
        if (is_duplicate_line(current->data, cads_context->labels)) {
            dprintf(2, ERR(ERRMSG_DUPLBLLINE),
                ((label_t *)current->data)->line + 1);
            free_warray(file);
            free_labels(cads_context);
            return 84;
        }
    }
    return 0;
}

static int load_and_check(char ***file, int argc, char **argv)
{
    if (argc < 2) {
        dprintf(2, ERR(ERRMSG_NEARGS));
        return 1;
    }
    *file = read_file(argv[1]);
    if (*file == 0) {
        dprintf(2, ERR(ERRMSG_FILERR), argv[1]);
        return 1;
    }
    return 0;
}

static void print_instructions(cads_context_t *context)
{
    for (node_t *current = context->opcodes->head;
        current; current = current->next) {
        printf("%s", instructions[
            ((instruction_t *)current->data)->iid
        ]);
        for (int i = 0; i < MAX_OPERAND_COUNT; i++) {
            printf(" %c", OP_TO_CHAR[((instruction_t *)current->data)
                ->operand_types[i]]);
            printf("%-6i", *((int *)(((instruction_t *)current->data)
                ->operand_values[i])));
        }
        printf("\n");
    }
    return;
}

static int dump_binary(cads_context_t *context, char *filepath)
{
    int fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0755);

    if (fd == -1) {
        dprintf(2, ERR(ERRMSG_FILERRCREAT), filepath);
        return 1;
    }
    write(fd, SHEBANG, sizeof(SHEBANG) - 1);
    for (node_t *current = context->opcodes->head;
        current; current = current->next) {
        write(fd, current->data, sizeof(instruction_t));
    }
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{
    char **file = 0;
    cads_context_t context;

    if (load_and_check(&file, argc, argv)) {
        return 84;
    }
    remove_comments(file);
    if (parse_error(&context, file) ||
        parse_non_error(&context, file)) {
        return 84;
    }
    load_file(&context, file);
    print_instructions(&context);
    dump_binary(&context, "test.cadb");
    load_vm(&context, "test.cadb");
    free_cads_context(&context);
    free_warray(file);
    return 0;
}
