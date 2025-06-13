CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = sorgente
TEST_DIR = test

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_FILES_NO_MAIN = $(filter-out $(SRC_DIR)/car_sharing.o, $(OBJ_FILES))

TEST_SRC = $(TEST_DIR)/test.c
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET_MAIN = car_sharing
TARGET_TEST = test_file

.PHONY: all clean

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET_TEST): $(OBJ_FILES_NO_MAIN) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET_MAIN) $(TARGET_TEST)