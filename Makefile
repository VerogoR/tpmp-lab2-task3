# Makefile для сборки программы "Блокнот" (модель КИС-2)
# Исходники в src/, заголовки в include/

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -Iinclude
LDFLAGS =

SRCDIR = src
INCDIR = include
OBJDIR = bin
TARGET = blocknote

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/note_server.c
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/note_server.o

.PHONY: all clean run

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

$(OBJDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/note.h
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)/main.c

$(OBJDIR)/note_server.o: $(SRCDIR)/note_server.c $(INCDIR)/note.h
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)/note_server.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
