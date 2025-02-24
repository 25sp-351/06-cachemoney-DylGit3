CC = gcc
CFLAGS = -Wall -g -I.
OBJFILES = money.o cache.o main.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGET)

money.o: money.c money.h
	$(CC) $(CFLAGS) -c money.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

main.o: main.c money.h cache.h
	$(CC) $(CFLAGS) -c main.c

run: $(TARGET)
	$(TARGET).exe < input.txt

clean:
	del /F /Q $(OBJFILES) $(TARGET) 2>nul

.PHONY: all clean run
