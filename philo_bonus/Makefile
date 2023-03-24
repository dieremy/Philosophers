BRIGHT_BLUE=\e[0;94m
MAGENTA=\e[0;35m
DEFAULT=\e[0m

SRC_B = start_b.c main_b.c utils_b.c
OBJ_B = $(SRC_B:.c=.o)
CC = gcc -g
FLAGS = -pthread -Wall -Werror -Wextra
NAME_B = philo_bonus

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ 

$(NAME_B): $(OBJ_B)
	@$(CC) $(FLAGS) $(OBJ_B) -o $(NAME_B)
	@echo "$(BRIGHT_BLUE)./$(NAME_B) CREATION$(DEFAULT)"

all: $(NAME_B)

clean:
	@rm -f $(OBJ_B)
	@echo "$(MAGENTA)bonus objs DELETION$(DEFAULT)"

fclean: clean
	@rm -f $(NAME_B)
	@echo "$(MAGENTA)./$(NAME_B) DELETION, CLEAN & PERFUMED$(DEFAULT)"

re: fclean all
	@echo "$(BRIGHT_BLUE)RECOMMENCE$(DEFAULT)"

.PHONY : clean fclean all 