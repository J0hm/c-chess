CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Ilib/unity -MMD -MP -O3
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
LIB_DIR = lib/unity
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_NO_MAIN = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_NO_MAIN))
DEPS = $(OBJS:.o=.d)

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRCS))

UNITY_SRC = $(LIB_DIR)/unity.c
UNITY_OBJ = $(OBJ_DIR)/unity.o

TARGET = $(BIN_DIR)/main

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/unity.o: $(UNITY_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

test: $(TEST_BINS)
	@echo "Running unit tests..."
	@for test in $(TEST_BINS); do \
		./$$test; \
	done;

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJS_NO_MAIN) $(UNITY_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@