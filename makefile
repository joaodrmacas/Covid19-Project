#Compiler
CC = gcc
#Compile flags
CFLAGS = -Wall -std=c11 -O3 -g -o
#Executable name
TARGET = covid19
#C files
CF = main.c checkInput.c readWrite.c free.c sort.c restricoes.c selecao.c general.c

all:
	$(CC) $(CFLAGS) $(TARGET) $(CF)

clean:
	rm $(TARGET)
