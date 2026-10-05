CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude

LDFLAGS = -lreadline

SRC = main.c \
      src/executor.c \
      src/builtin.c \
      src/jobs.c \
      src/job_control.c \
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
