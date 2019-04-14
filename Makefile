NAME = ls

SRC=$(wildcard src/*.c)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iincludes -g -fsanitize=address
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)

obj:
	mkdir obj

obj/%.o: src/%.c
	gcc $(CFLAGS) $(OPTION) -c -o $@ $<

$(NAME): obj $(OBJ)
	cd lib/libftprintf && make -f Makefile
	mv lib/libftprintf/libftprintf.a .
	$(CC) -o $(NAME) $(CFLAGS) $(SRC) libftprintf.a

clean:
	-cd lib/libftprintf && make clean
	-rm -rf obj

fclean: clean
	-rm -f $(NAME)
	-rm -f libftprintf.a

re: fclean $(NAME)

.PHONY: clean fclean re
