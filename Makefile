CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = src/stack.c src/queue.c src/linked_list.c src/doubly_linked_list.c src/circular_linked_list.c src/hash_set.c src/hash_map.c
OBJ = $(SRC:.c=.o)
LIB = libds.a

LEETCODE_SRC = tests/leetcode_test/two_sum.c tests/leetcode_test/valid_parentheses.c tests/leetcode_test/contains_duplicate.c tests/leetcode_test/merge_two_sorted_lists.c
LEETCODE_OBJ = $(LEETCODE_SRC:.c=.o)
LEETCODE_PROGS = $(LEETCODE_SRC:tests/leetcode_test/%.c=%)

all: $(LIB) test leetcode

# Build static library
$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

# Build main test program
test: tests/main.c $(LIB)
	$(CC) $(CFLAGS) tests/main.c -L. -lds -o testprog

# Build LeetCode test programs
leetcode: $(LEETCODE_PROGS)

$(LEETCODE_PROGS): %: tests/leetcode_test/%.c $(LIB)
	$(CC) $(CFLAGS) tests/leetcode_test/$@.c -L. -lds -o tests/leetcode_test/$@

# Run all test programs
run: test leetcode
	./testprog
	$(foreach prog,$(LEETCODE_PROGS),./tests/leetcode_test/$(prog);)

clean:
	rm -f $(OBJ) $(LIB) testprog $(LEETCODE_OBJ) $(foreach prog,$(LEETCODE_PROGS),tests/leetcode_test/$(prog))

.PHONY: all test leetcode run clean