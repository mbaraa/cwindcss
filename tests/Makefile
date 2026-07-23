.PHONY: build run
BINARY_NAME=tests

all: build

build:
	gcc -fsanitize=address -std=c23 unity.c main.c ../libcwindcss.a -o $(BINARY_NAME)

run:
	./$(BINARY_NAME)

clean:
	-rm $(BINARY_NAME)
