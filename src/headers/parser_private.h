#pragma once

#include "repl.h"

#define TABLE_MAX_ROWS 10

typedef enum { INSERT, SELECT, DELETE, ROLLBACK } StatementType;

typedef enum {
    STATEMENT_RECOGNIZED,
    STATEMENT_UNRECOGNIZED
} StatementRecognitionResult;

typedef struct {
    StatementType type;
    size_t id;
    char username[32];
} Statement;

typedef void (*ExecutorFunction)(Statement* statement);

typedef struct {
    const char* keyword;
    StatementType type;
    ExecutorFunction function;
} KeywordMapping;

typedef struct {
    size_t id;
    char username[32];
} Row;

typedef struct {
    Row rows[TABLE_MAX_ROWS];
    size_t num_rows;
} Table;
