##
## Makefile for  in /home/sabour_f/aes
##
## Made by Florian SABOURIN
## Login   <sabour_f@epitech.net>
##
## Started on  Sat Sep 19 16:06:02 2015 Florian SABOURIN
## Last update Sat Sep 19 16:06:02 2015 Florian SABOURIN
##

# Executables
CC		=	gcc
CXX		=	g++
AR		=	ar rcs
RM		=	@rm -vf
MAKE		+=	--no-print-directory

# Names
NAME		=	moulicl

# Flags
CFLAGS		=	-Wall -W -Wshadow -fno-diagnostics-show-caret -ggdb3 -Iinclude 
CXXFLAGS	=	-Wall -W -Wshadow -fno-diagnostics-show-caret -ggdb3 -Iinclude 
LDFLAGS		=	

# Files
CSRC		=	src/run.c
CSRC		+=	src/config.c
CSRC		+=	src/main.c
CSRC		+=	src/moulicl.c
CSRC		+=	src/aes.c


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

src/run.o: src/run.c include/moulicl.h include/config.h
	$(CC) $(CFLAGS) -c -o src/run.o src/run.c

src/config.o: src/config.c include/config.h
	$(CC) $(CFLAGS) -c -o src/config.o src/config.c

src/main.o: src/main.c include/config.h include/moulicl.h
	$(CC) $(CFLAGS) -c -o src/main.o src/main.c

src/moulicl.o: src/moulicl.c include/moulicl.h include/config.h
	$(CC) $(CFLAGS) -c -o src/moulicl.o src/moulicl.c

src/aes.o: src/aes.c
	$(CC) $(CFLAGS) -c -o src/aes.o src/aes.c

