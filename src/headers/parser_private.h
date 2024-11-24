#pragma once

#include "repl.h"

#define TABLE_MAX_ROWS 10
#define FILENAME "database.db"

typedef enum { INSERT, SELECT, DELETE, ROLLBACK } StatementType;

typedef enum {
    STATEMENT_RECOGNIZED,
    STATEMENT_UNRECOGNIZED,
    STATEMENT_INCOMPLETE,
} StatementRecognitionResult;

typedef struct {
    char username[32];
    size_t id;
} Row;

typedef struct {
    Row rows[TABLE_MAX_ROWS];
    size_t num_rows;
} Table;

typedef struct {
    StatementType type;
    Row data;
} Statement;

typedef void (*ExecutorFunction)(Statement* statement);

typedef struct {
    const char* keyword;
    StatementType type;
    ExecutorFunction function;
} KeywordMapping;
