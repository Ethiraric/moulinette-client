##
## Makefile for  in /home/sabour_f/aes
##
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
##
## Started on  Sat Sep 19 12:03:09 2015 Florian SABOURIN
## Last update Sat Sep 19 12:03:09 2015 Florian SABOURIN
##

# Executables
CC		=	gcc
CXX		=	g++
AR		=	ar rcs
RM		=	@rm -vf
MAKE		+=	--no-print-directory

# Names
NAME		=	mouli

# Flags
CFLAGS		=	-Wall -W -Wshadow -fno-diagnostics-show-caret -I. 
CXXFLAGS	=	-Wall -W -Wshadow -fno-diagnostics-show-caret -I. 
LDFLAGS		=	

# Files
CSRC		=	./config.c
CSRC		+=	./main.c
CSRC		+=	./aes.c


# Objects
OBJ		=	$(CSRC:.c=.o) $(CXXSRC:.cpp=.o)

# Rules
$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(NAME)

re: fclean all

.PHONY: 	all clean fclean re

./config.o: ./config.c ./config.h
	$(CC) $(CFLAGS) -c -o ./config.o ./config.c

./main.o: ./main.c ./config.h
	$(CC) $(CFLAGS) -c -o ./main.o ./main.c

./aes.o: ./aes.c
	$(CC) $(CFLAGS) -c -o ./aes.o ./aes.c

