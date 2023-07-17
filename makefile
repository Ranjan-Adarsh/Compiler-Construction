CC = gcc
CFLAGS = -Wall

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

TARGET = compiler

.PHONY: all clean

all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

# nasm:
# 	nasm -felf64 code.asm 
# 	gcc -no-pie code.o -o asmfile -nostdlib
# 	 ./asmfile
nasm:
	nasm -f elf64 -g code.asm -o code.o
	gcc -no-pie -m64 code.o -o code