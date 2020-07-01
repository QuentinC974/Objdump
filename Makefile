##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## CPD10ysk01
##

SRC1	=	objdump64.c \
			objdump32.c \
			main_objdump.c \

TEST	=
OBJ1	=	$(SRC1:.c=.o)

NAME1	=	my_objdump

UNIT_TEST   =	unit_tests

CFLAGS	=	-g -g3 -W -Wall -Wextra -ggdb

FDFLAGS	=	$(CFLAGS) -lcriterion --coverage

all:		objdump

objdump:	$(OBJ1)
		gcc -o $(NAME1) $(OBJ1)

tests_run:
		g++ -o $(UNIT_TEST) $(TEST) $(LIB) $(FDFLAGS)
		./unit_tests

clean:
		rm -f $(OBJ1)
		rm -rf	*.gc*

fclean:	clean
		rm -f $(NAME1)
		rm -f $(UNIT_TEST)

re: fclean all


.PHONY:		all tests_run clean fclean re