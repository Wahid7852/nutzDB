#include "headers/repl.h"
#include "headers/parser.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static InputBuffer _new_input_buffer(void);
static void _print_prompt(void);
static void _read_input(InputBuffer* input_buffer);
static void _clear_buffer(InputBuffer* input_buffer);

/***************************************************************
                        PUBLIC FUNCTIONS
****************************************************************/
void init_repl(void) {
    InputBuffer input_buffer = _new_input_buffer();
    printf(".exit to Exit\n");
    while (1) {
        _print_prompt();
        _read_input(&input_buffer);
        if (input_buffer.buffer[0] == '.') {
            if (strcmp(input_buffer.buffer, ".exit") == 0) {
                _clear_buffer(&input_buffer);
                printf("GOODBYE!\n");
                exit(EXIT_SUCCESS);
            } else {
                printf("Unrecognized meta command '%s'\n", input_buffer.buffer);
                continue;
            }
        }
        Parser(&input_buffer);
    }
}

/***************************************************************
                        PRIVATE FUNCTIONS
****************************************************************/
static InputBuffer _new_input_buffer(void) {
    InputBuffer input_buffer = {
        .buffer = NULL, .buffer_length = 0, .input_length = 0};
    return input_buffer;
}

static void _print_prompt(void) {
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
    input_buffer->buffer = NULL;
}
