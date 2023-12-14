TARGET = lab1
CC = gcc
# CFLAGS = -mavx2 -msse4.1 -msse3 -maes -march=native -mtune=generic#-Wall
CFLAGS = -mavx -mavx2 -msse4.1 -march=native -mtune=generic -g -O3 -fsanitize=address#-Wall

SRC_DIR = ./src/
OBJ_DIR = ./obj/
ASM_DIR = ./asm/


SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c 
	$(CC) $(CFLAGS) -S -fverbose-asm -g  $< -o $(ASM_DIR)$@.asm
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	rm $(TARGET) $(OBJ_DIR)*.o $(ASM_DIR)$(OBJ_DIR)*.asm
