#include "headers/repl.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct InputBuffer {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};

static InputBuffer* _new_input_buffer();
static void _print_prompt();
static void _read_input(InputBuffer*);
static void _clear_buffer(InputBuffer*);

/***************************************************************
                        PUBLIC FUNCTIONS
****************************************************************/
void init_repl() {
    InputBuffer* input_buffer = _new_input_buffer();
    if (!input_buffer) {
        fprintf(stderr, "Error: Failed to allocate memory for InputBuffer\n");
        exit(EXIT_FAILURE);
    }
    printf(".exit to Exit\n");
    while (1) {
        _print_prompt();
        _read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            _clear_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'\n", input_buffer->buffer);
        }
    }
}

/***************************************************************
                        PRIVATE FUNCTIONS
****************************************************************/
static InputBuffer* _new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

static void _print_prompt() {
    printf("nutzdb > ");
}

static void _read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read =
        getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        _clear_buffer(input_buffer);
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

static void _clear_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}
