//A simple Makefile to compile the C program. It allows overriding the header file, which is useful for the round-trip validation step//
# Compiler and flags
CC = gcc
CFLAGS = -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lcyaml

# Source files and executable
SRC = main.c
EXEC = yaml_emitter

# Allow overriding the header file from the command line
HEADER_FILE ?= instructions.h

# Add a CFLAG to specify the include path for the header
CFLAGS += -DHEADER_FILE=\"$(HEADER_FILE)\"

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

clean:
	rm -f $(EXEC) *.o

.PHONY: all clean  
