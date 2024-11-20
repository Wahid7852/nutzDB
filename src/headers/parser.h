#pragma once

#include "repl.h"

typedef enum { INSERT, SELECT, DELETE, ROLLBACK } StatementType;

typedef enum {
    STATEMENT_RECOGNIZED,
    STATEMENT_UNRECOGNIZED
} StatementRecognitionResult;

typedef void (*ExecutorFunction)(void);

typedef struct {
    const char* keyword;
    StatementType type;
    ExecutorFunction function;
} KeywordMapping;

typedef struct {
    StatementType type;
} Statement;

void Parser(InputBuffer* input_buffer);
