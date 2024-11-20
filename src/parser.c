#include "headers/parser.h"
#include "headers/repl.h"

#include <stdio.h>
#include <string.h>

typedef enum { INSERT, SELECT, DELETE } StatementType;
typedef enum {
    STATEMENT_RECOGNIZED,
    STATEMENT_UNRECOGNIZED
} StatementRecognitionResult;

struct Statement {
    StatementType type;
};

static StatementRecognitionResult _make_statement(InputBuffer* input_buffer,
                                                  Statement* statement);
static void _statement_executer(Statement* statement);

/***************************************************************
                        PUBLIC FUNCTIONS
****************************************************************/
void Parser(InputBuffer* input_buffer) {
    Statement statement;
    switch (_make_statement(input_buffer, &statement)) {
        case (STATEMENT_RECOGNIZED):
            _statement_executer(&statement);
            break;
        case (STATEMENT_UNRECOGNIZED):
            printf("Unrecognized '%s'.\n", input_buffer->buffer);
    }
}

/***************************************************************
                        PRIVATE FUNCTIONS
****************************************************************/
static StatementRecognitionResult _make_statement(InputBuffer* input_buffer,
                                                  Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = INSERT;
        return STATEMENT_RECOGNIZED;
    } else if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = SELECT;
        return STATEMENT_RECOGNIZED;
    } else if (strncmp(input_buffer->buffer, "delete", 6) == 0) {
        statement->type = DELETE;
        return STATEMENT_RECOGNIZED;
    }
    return STATEMENT_UNRECOGNIZED;
}

static void _statement_executer(Statement* statement) {
    switch (statement->type) {
        case (INSERT):
            printf("INSERT goes here\n");
            break;
        case (SELECT):
            printf("SELECT goes here\n");
            break;
        case (DELETE):
            printf("DELETE goes here\n");
            break;
    }
}
