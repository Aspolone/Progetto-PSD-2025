CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = sorgente

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

TARGET_MAIN = car_sharing

.PHONY: all clean

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET_MAIN)