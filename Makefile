CC := gcc

CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -g -Iinclude

TARGET := main

SRC := main.c $(shell find src -name '*.c')
OBJ := $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	find . -name '*.o' -delete
	rm -f $(TARGET)

rebuild: clean $(TARGET)

.PHONY: run clean rebuild