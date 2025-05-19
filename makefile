CC = gcc
CFLAGS = -Isrc -Itest
OBJS = test/test.c src/cstr8.c
EXEC = build/cstr8

all:
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
