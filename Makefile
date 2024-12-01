CC = gcc
CFLAGS = -Ilib -Wall

SRC_DIR = $(shell find . -type d -name "c")
LIB_SRC = ../../lib/vector/vector.c

all: day-1-1 day-2-1

day-1-1: day-1/c/q1.c
	cd day-1/c && $(CC) $(CFLAGS) -o q1 q1.c $(LIB_SRC) && ./q1

day-2-1: day-2/c/q1.c
	cd day-2/c && $(CC) $(CFLAGS) -o q1 q1.c $(LIB_SRC) && ./q1

clean:
	find . -type f -name "q1" -exec rm -f {} +
