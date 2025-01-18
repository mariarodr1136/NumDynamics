# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm

# Project files
TARGET = ass1
SOURCE = random_number_generator.c

# Python script files
PYTHON_SCRIPTS = generate_histogram_data.py calculate_statistics.py

# Default target
all: $(TARGET)
	./$(TARGET)
	python3 $(PYTHON_SCRIPTS)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LIBS)

# Clean up compiled files and generated data
clean:
	rm -f $(TARGET)
	rm -rf DATA/
	rm -rf HISTOGRAM/

# Print help information
help:
	@echo "Available commands:"
	@echo "  make      - Compile and run the program, followed by Python scripts"
	@echo "  make clean- Remove executable and generated data"
	@echo "  make help - Display this help message"

.PHONY: all clean help
