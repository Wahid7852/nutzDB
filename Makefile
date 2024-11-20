CC = clang
CFLAGS = -Wall -Wextra

TARGET = nutzDB
SOURCES = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -f $(TARGET)
