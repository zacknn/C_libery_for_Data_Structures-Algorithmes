CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = src/stack.c src/queue.c src/linked_list.c src/circular_linked_list.c src/doubly_linked_list.c
OBJ = $(SRC:.c=.o)
LIB = libds.a

all: $(LIB) test

# Build static library
$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

# Build test program (links with our library)
test: tests/main.c $(LIB)
	$(CC) $(CFLAGS) tests/main.c -L. -lds -o testprog

clean:
	rm -f $(OBJ) $(LIB) testprog
