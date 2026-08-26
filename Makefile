CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lreadline

SRC = main.c \
      src/executor.c \
      src/builtin.c \
      src/expand.c \
      src/history.c \
      src/lexer.c \
      src/parser.c \
      src/token.c

TARGET = shellforge

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
