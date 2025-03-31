CC = gcc
CFLAGS = -std=c11 -Idfunc -Ijlib

SRCS = dfunc/*.c jlib/*.c tester/*.c
TARGET = bin/tester

all:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -rf bin

run:
	clear
	./bin/tester