#pragma once

#include <stdlib.h>

// Revisit this when I've fleshed it out more.
#define MAX_ARGS 8

typedef struct bolt_func_arg_s {
    long id;
    long type;
} bolt_func_arg_t;

typedef struct bolt_func_s {
    long id;

    int args_count;
    bolt_func_arg_t *args[MAX_ARGS];

    int length;
    char *func_block;
} bolt_func_t;

bolt_func_t *bolt_func_create(long id) {
    bolt_func_t *func = malloc(sizeof(bolt_func_t));

    func->id = id;

    return func;
}
