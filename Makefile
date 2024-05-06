CC = gcc
CFLAGS=-g -Wall -Wextra -O -pthread
FILE = main.c
OBJ_FILE = main

all: 
	$(CC) $(CFLAGS) $(FILE) -o $(OBJ_FILE)

run:
	./$(OBJ_FILE)