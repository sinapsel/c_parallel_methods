TARGET = lab2
CC = gcc
CFLAGS = -mavx -pthread -fopenmp -O1 #-mwindows #-fsanitize=address #-Wall

SRC_DIR = ./src/
OBJ_DIR = ./obj/
# ASM_DIR = ./asm/


SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	rm $(TARGET) $(OBJ_DIR)*.o
