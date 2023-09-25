CC = gcc
HEADER_DIR = include
CFLAGS = -w -Wall -O2 -I$(HEADER_DIR)
SRCDIR = src
BINDIR = bin

LIBS = 

all: $(BINDIR)/main run clean

$(BINDIR)/main: $(SRCDIR)/main.c
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

run: 
	@./$(BINDIR)/main

clean:
	@rm "$(BINDIR)/main"