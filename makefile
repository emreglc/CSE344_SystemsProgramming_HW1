# Define the compiler
CC = gcc

# Define the flags
CFLAGS = -Wall -g

# Define the target executable
TARGET = fileManager

# Define the source files
SRCS = main.c fileManagerLib.c helpers.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the libraries to link against
LIBS = -lm

# Default target
all: $(TARGET) cleanup

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove unnecessary object files
cleanup:
	@find . -name "*.o" -type f -delete

# Clean up all build files
clean:
	rm -f $(OBJS) $(TARGET)
