# Makefile for your multithreaded CPU monitor program

CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -pthread

SOURCES = reader.c analyzer.c printer.c cpu_monitor.c main.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = main

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
