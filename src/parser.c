#include "headers/parser.h"
#include "headers/repl.h"

#include <stdio.h>
#include <string.h>

/***************************************************************
                    PRIVATE INITIALIZATION STUFF
****************************************************************/
static StatementRecognitionResult _make_statement(InputBuffer* input_buffer,
                                                  Statement* statement);
static void _statement_executer(Statement* statement);

static void insert_execute(void);
static void select_execute(void);
static void delete_execute(void);
static void rollback_execute(void);

const KeywordMapping mappings[] = {{"insert", INSERT, insert_execute},
                                   {"select", SELECT, select_execute},
                                   {"delete", DELETE, delete_execute},
                                   {"rollback", ROLLBACK, rollback_execute}};

const size_t num_mappings = sizeof(mappings) / sizeof(mappings[0]);

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
    for (size_t i = 0; i < num_mappings; ++i) {
        if (strncmp(input_buffer->buffer, mappings[i].keyword,
                    strlen(mappings[i].keyword)) == 0) {
            statement->type = mappings[i].type;
            return STATEMENT_RECOGNIZED;
        }
    }
    return STATEMENT_UNRECOGNIZED;
}

static void _statement_executer(Statement* statement) {
    for (size_t i = 0; i < num_mappings; ++i) {
        if (mappings[i].type == statement->type) {
            mappings[i].function();
            break;
        }
    }
}

static void insert_execute(void) {
    printf("INSERT goes here\n");
}

static void select_execute(void) {
    printf("SELECT goes here\n");
}

static void delete_execute(void) {
    printf("DELETE goes here\n");
}

static void rollback_execute(void) {
    printf("ROLLBACK goes here\n");
}
