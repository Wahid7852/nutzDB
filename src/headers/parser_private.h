#pragma once

#include "repl.h"

// Internal types and enums
typedef enum { INSERT, SELECT, DELETE, ROLLBACK } StatementType;

typedef enum {
    STATEMENT_RECOGNIZED,
    STATEMENT_UNRECOGNIZED
} StatementRecognitionResult;

typedef struct {
    StatementType type;
} Statement;

// Function pointer for executor functions
typedef void (*ExecutorFunction)(void);

typedef struct {
    const char* keyword;
    StatementType type;
    ExecutorFunction function;
} KeywordMapping;
