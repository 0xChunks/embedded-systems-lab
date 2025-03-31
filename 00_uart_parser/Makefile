CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = uart_parser
SRCS = main.c commands.c

#Build Rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	@echo "Build complete. Run './$(TARGET)' to execute."
	@echo "To clean up, run 'make clean'."

# Clean Rule
clean:
	rm -f $(TARGET)
	@echo "Cleaned up build files."
	@echo "To build again, run 'make all'."