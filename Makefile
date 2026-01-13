CC = gcc
CFLAGS = -Wall

SRC = src/c_engine/main.c src/c_engine/bst.c

BUILD_DIR = build
TARGET = $(BUILD_DIR)/balancer

all: $(TARGET)
$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "Build successful..."

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	@echo "Cleaned..."