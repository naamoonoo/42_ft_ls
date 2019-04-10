NAME=libftprintf.a

SRC=$(wildcard src/*.c)
LRC=$(wildcard lib/libft/*.c)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iincludes
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
LOBJ = $(patsubst %.c, %.o, $(LRC))

all: $(NAME)

$(NAME): obj $(OBJ) $(LOBJ)
	ar rc $(NAME) $(OBJ) $(LOBJ)
	ranlib $(NAME)

obj:
	mkdir obj

obj/%.o: src/%.c
	gcc $(CFLAGS) $(OPTION) -c -o $@ $<

clean:
	-cd lib/libft && make clean

fclean: clean
	-cd lib/libft && make fclean
	-rm -f $(NAME)
	-rm -rf obj
	-rm -f libft.a

re: fclean $(NAME)

.PHONY: clean fclean re
