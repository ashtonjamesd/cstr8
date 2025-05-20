CC = gcc
CFLAGS = -Isrc -Itest
OBJS = test/tests.c src/cstr8.c
EXEC = build/cstr8

all:
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
