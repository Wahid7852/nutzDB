#include "headers/repl.h"
#include "headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

static inputbuffer_t* new_input_buffer(void);
static void print_prompt(void);
static int read_input(inputbuffer_t* input_buffer);
static void clear_buffer(inputbuffer_t* input_buffer);

/*******************************************************************************
                                PUBLIC FUNCTIONS
*******************************************************************************/
void init_repl(void) {
    inputbuffer_t* input_buffer = new_input_buffer();
    
    printf(".exit to Exit\n");

    while (1) {
        print_prompt();
        clear_buffer(input_buffer);        

        if (read_input(input_buffer) != 0) {
            break;
        }

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            printf("GOODBYE!\n");
            break;
        }

        if (input_buffer->buffer[0] == '.') {
            printf("Unrecognized meta command '%s'\n", input_buffer->buffer);
            continue;
        }

        Parser(input_buffer);
    }

    clear_buffer(input_buffer);
    free(input_buffer);
}
/*******************************************************************************
                               PRIVATE FUNCTIONS
*******************************************************************************/
static inputbuffer_t* new_input_buffer(void) {
    inputbuffer_t* input_buffer = malloc(sizeof(inputbuffer_t));
    if (!input_buffer) {
        fprintf(stderr, "Memory allocation failed for input buffer\n");
        exit(EXIT_FAILURE);
    }
    
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    
    return input_buffer;
}

static void print_prompt(void) {
    printf("nutzdb > ");
    fflush(stdout);
}

static int read_input(inputbuffer_t* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), 
                                 &(input_buffer->buffer_length), 
                                 stdin);
    
    if (bytes_read <= 0) {
        if (feof(stdin)) {
            printf("\nEOF detected. Exiting.\n");
            return -1;
        }
        
        fprintf(stderr, "Error reading input\n");
        return -1;
    }

    if (bytes_read > 0 && input_buffer->buffer[bytes_read - 1] == '\n') {
        input_buffer->buffer[bytes_read - 1] = '\0';
        input_buffer->input_length = bytes_read - 1;
    } else {
        input_buffer->input_length = bytes_read;
    }

    return 0;
}

static void clear_buffer(inputbuffer_t* input_buffer) {
    if (input_buffer && input_buffer->buffer) {
        free(input_buffer->buffer);
        input_buffer->buffer = NULL;
        input_buffer->buffer_length = 0;
        input_buffer->input_length = 0;
    }
}
