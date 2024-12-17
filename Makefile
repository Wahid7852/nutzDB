ifeq ($(BUILD_TYPE),release)
	CC = gcc
	CFLAGS = -O3 -funroll-loops -ftree-vectorize -fstrict-overflow -DNDEBUG
else
	CC = clang
	CFLAGS = -O0 -Wall -Wextra -pedantic
endif

TARGET = nutzDB
SOURCES = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean

clean:
	rm -f $(TARGET)