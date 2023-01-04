CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRC = my_printf.c
TARGET = my_printf
OBJ = $(SRC: .c = .o)


all : $(TARGET)

$(TARGET) : $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ) 

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)
	
re: fclean all
