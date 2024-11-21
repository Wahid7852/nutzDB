#include "headers/parser.h"
#include "headers/parser_private.h"
#include "headers/repl.h"

#include <stdio.h>
#include <string.h>

/***************************************************************
                   PRIVATE INITIALIZATION STUFF
****************************************************************/
static StatementRecognitionResult _make_statement(InputBuffer* input_buffer,
                                                  Statement* statement);
static void _statement_executer(Statement* statement);
static void _debug_table(Table* table);

static void _insert_execute(Statement* statement);
static void _select_execute(Statement* statement);
static void _delete_execute(Statement* statement);
static void _rollback_execute(Statement* statement);

const KeywordMapping mappings[] = {{"insert", INSERT, _insert_execute},
                                   {"select", SELECT, _select_execute},
                                   {"delete", DELETE, _delete_execute},
                                   {"rollback", ROLLBACK, _rollback_execute}};

const size_t num_mappings = sizeof(mappings) / sizeof(mappings[0]);

Table db = {.num_rows = 0};

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
            if (statement->type == INSERT) {
                size_t id;
                char username[32];
                if (sscanf(input_buffer->buffer, "insert %zu %31s", &id,
                           username) < 2) {
                    printf(
                        "Syntax error. Correct usage: insert <id> "
                        "<username>\n");
                    return STATEMENT_UNRECOGNIZED;
                }
                // printf("id = %zu and username = %s\n", id, username);
                statement->id = id;
                strncpy(statement->username, username,
                        sizeof(statement->username));
            }
            return STATEMENT_RECOGNIZED;
        }
    }
    return STATEMENT_UNRECOGNIZED;
}

static void _statement_executer(Statement* statement) {
    for (size_t i = 0; i < num_mappings; ++i) {
        if (mappings[i].type == statement->type) {
            mappings[i].function(statement);
            break;
        }
    }
}

static void _debug_table(Table* table) {
    for (size_t i = 0; i < table->num_rows; ++i) {
        printf("id -> %zu & username -> %s\n", table->rows[i].id,
               table->rows[i].username);
    }
}

static void _insert_execute(Statement* statement) {
    if (db.num_rows >= TABLE_MAX_ROWS) {
        printf("Error: Table full.\n");
        return;
    }
    Row* row = &db.rows[db.num_rows++];
    row->id = statement->id;
    strncpy(row->username, statement->username, sizeof(row->username));
    _debug_table(&db);
}

static void _select_execute(Statement* statement) {
    (void)statement;
    printf("SELECT goes here\n");
}

static void _delete_execute(Statement* statement) {
    (void)statement;
    printf("DELETE goes here\n");
}

static void _rollback_execute(Statement* statement) {
    (void)statement;
    printf("ROLLBACK goes here\n");
}
