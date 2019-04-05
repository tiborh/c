CC=gcc
CFLAGS=-std=c99 -Wall -Werror
LDLIBS=-lm # sometimes LDFLAGS also works

#%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $< $(LDLIBS)
	