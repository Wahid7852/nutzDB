#pragma once

#include <stdlib.h>

typedef struct {
    char *buffer;
    size_t buffer_length;
    size_t input_length;
} inputbuffer_t;

void init_repl(void);
