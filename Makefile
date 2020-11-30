C_FILES=hash_map.c list.c queue.c stack.c
H_FILES=$(C_FILES:.c=.h) memory.h
O_FILES=$(C_FILES:.c=.o)

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

%.o: %.c $(H_FILES)
	$(CC) -c -o $@ $< $(CFLAGS)

lib: $(O_FILES)
	ar -cvq libdatastructures.a *.o

test:
	$(CC) $(CFLAGS) test.c C_FILES

.PHONY: clean
clean:
	rm -f *.o