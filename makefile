CC = gcc
CFLAGS = -Isrc -Itest -fsanitize=address -g
OBJS = test/tests.c src/strizzle.c
EXEC = build/cstr8

all:
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
