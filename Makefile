CC      = gcc
CFLAGS  = -Iinclude -Wall -Wextra
AR      = ar
ARFLAGS = rcs

# Directories
SRC_DIR     = src
TEST_DIR    = tests
LC_DIR      = tests/leetcode_test

# Library name
LIB = libds.a

# ===============================
# Library sources (AUTO)
# ===============================
SRC := $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)

# ===============================
# Main tests
# ===============================
TEST_SRC      = $(TEST_DIR)/main.c
TEST_BIN      = testprog
NAND_TEST_SRC = $(TEST_DIR)/nand_test.c
NAND_TEST_BIN = nand_test

# ===============================
# LeetCode tests (AUTO)
# ===============================
LC_SRC  := $(wildcard $(LC_DIR)/*.c)
LC_BIN  := $(patsubst $(LC_DIR)/%.c,$(LC_DIR)/%,$(LC_SRC))

# ===============================
# Targets
# ===============================
all: $(LIB) test leetcode

# Static library
$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Generic compile rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Main tests
test: $(TEST_BIN) $(NAND_TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB)
	$(CC) $(CFLAGS) $< -L. -lds -o $@

$(NAND_TEST_BIN): $(NAND_TEST_SRC) $(LIB)
	$(CC) $(CFLAGS) $< -L. -lds -o $@

# LeetCode binaries
leetcode: $(LC_BIN)

$(LC_DIR)/%: $(LC_DIR)/%.c $(LIB)
	$(CC) $(CFLAGS) $< -L. -lds -o $@

# Run everything
run: test leetcode
	./$(TEST_BIN)
	./$(NAND_TEST_BIN)
	@for bin in $(LC_BIN); do $$bin; done

clean:
	rm -f $(OBJ) $(LIB) $(TEST_BIN) $(NAND_TEST_BIN) $(LC_BIN)

.PHONY: all test leetcode run clean