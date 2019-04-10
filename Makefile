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
	cd lib/libft && make -f Makefile
	mv lib/libft/libft.a .
	$(CC) -o $(NAME) $(CFLAGS) $(SRC) libft.a

clean:
	-cd lib/libft && make clean
	-rm -rf obj

fclean: clean
	-cd lib/libft && make fclean
	-rm -f $(NAME)
	-rm -rf obj
	-rm -f libft.a

re: fclean $(NAME)

.PHONY: clean fclean re
