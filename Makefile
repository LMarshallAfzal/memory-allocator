CFLAGS = -g -Wall
INCLUDES = -Iinclude

LDLIBS = -lc

SRC_DIRS = src tests
OBJ_DIR = build/obj
EXEC_DIR = .

EXEC = test_allocator

# Build rules
all: $(EXEC_DIR)/test_allocator

$(EXEC_DIR)/test_allocator: $(OBJ_DIR)/allocator.o $(OBJ_DIR)/free.o $(OBJ_DIR)/malloc.o $(OBJ_DIR)/test_allocator.o
	gcc $(CFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

# Special rule for test_allocator (in tests directory)
$(OBJ_DIR)/test_allocator.o: tests/test_allocator.c | $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean

clean:
	rm -rf $(OBJ_DIR)

# Create build directories if they don't exist
build/obj:
	mkdir -p $@

run:
	./$(EXEC_DIR)/test_allocator

.PHONY: run