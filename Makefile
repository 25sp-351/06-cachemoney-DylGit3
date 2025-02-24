CC = gcc
CFLAGS = -Wall -g -I.
OBJFILES = money_to_string.o cache.o main.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGET)

money_to_string.o: money_to_string.c money_to_string.h
	$(CC) $(CFLAGS) -c money_to_string.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

main.o: main.c money_to_string.h cache.h
	$(CC) $(CFLAGS) -c main.c

run: $(TARGET)
	./$(TARGET) < input.txt

clean:
	rm -f $(OBJFILES) $(TARGET)

.PHONY: all clean run
