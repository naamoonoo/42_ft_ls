NAME = ft_ls

SRC=$(wildcard src/*.c)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iincludes
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)

obj:
	mkdir obj

obj/%.o: src/%.c
	gcc $(CFLAGS) $(OPTION) -c -o $@ $<

$(NAME): obj $(OBJ)
	cd lib/libftprintf && make
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
