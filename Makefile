CC = clang
CFLAGS = -Wall -Wextra -g

TARGET = nutzDB
SOURCES = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -f $(TARGET)
