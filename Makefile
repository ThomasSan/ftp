NAME = serveur
NAME2 = client

SRC = server.c misc.c x.c

INCLUDE = -I includes/

FLAG = -Wall -Werror -Wextra -g

LIBRARIES = -L libft/ -lft

CFILES = $(addprefix src/, $(SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c $(FLAG) $(INCLUDE) $(CFILES)
	@make -C libft/ fclean && make -C libft && make -C libft/ clean
	@gcc -o $(NAME) $(OBJ) $(LIBRARIES)
	@mkdir obj && mv $(OBJ) obj
	@echo ">>>$(NAME) READY<<<"

clean:
	@/bin/rm -rf obj
	@/bin/rm -rf $(OBJ)
	@echo "\x1b[0;01mclean\x1b[0;m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\x1b[0;01mfclean\x1b[0;m"

re: fclean all
