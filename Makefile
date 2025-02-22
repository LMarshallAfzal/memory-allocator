CFLAGS = -g -Wall
INCLUDES = -Iinclude -Itests -Itests/malloc -Itests/free

LDLIBS = -lcunit

SRC_DIRS = src
TEST_DIRS = tests
OBJ_DIR = build/obj
EXEC_DIR = .

EXEC = main_allocator
TEST_EXEC = test_allocator

# Build rules
all: $(EXEC_DIR)/$(EXEC) $(EXEC_DIR)/$(TEST_EXEC)

$(EXEC_DIR)/$(EXEC): $(OBJ_DIR)/allocator.o $(OBJ_DIR)/free.o $(OBJ_DIR)/malloc.o $(OBJ_DIR)/main.o
	gcc $(CFLAGS) -o $@ $^ $(LDLIBS)

$(EXEC_DIR)/$(TEST_EXEC): $(OBJ_DIR)/allocator.o $(OBJ_DIR)/free.o $(OBJ_DIR)/malloc.o $(OBJ_DIR)/test_runner.o $(OBJ_DIR)/test_malloc.o $(OBJ_DIR)/test_free.o $(OBJ_DIR)/test_allocator.o
	gcc $(CFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIRS)/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIRS)/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIRS)/malloc/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIRS)/free/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@


# Special rule for test_allocator (in tests directory)
$(OBJ_DIR)/test_allocator.o: tests/test_allocator.c | $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean

clean:
	rm -rf $(OBJ_DIR) $(EXEC_DIR)/$(EXEC) $(EXEC_DIR)/$(TEST_EXEC)

# Create build directories if they don't exist
$(OBJ_DIR):
	mkdir -p $@

run:
	./$(EXEC_DIR)/$(EXEC)

test:
	./$(EXEC_DIR)/$(TEST_EXEC)
