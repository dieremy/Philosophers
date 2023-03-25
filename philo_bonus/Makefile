# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 12:40:22 by robegarc          #+#    #+#              #
#    Updated: 2023/03/25 12:51:36 by robegarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BRIGHT_BLUE=\033[0;94m
MAGENTA=\033[0;35m
DEFAULT=\033[0m

SRC_B = start_bonus.c main_bonus.c utils_bonus.c
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
	@echo "$(MAGENTA)objs DELETION$(DEFAULT)"

fclean: clean
	@rm -f $(NAME_B)
	@echo "$(MAGENTA)./$(NAME_B) DELETION, CLEAN & PERFUMED$(DEFAULT)"

re: fclean all
	@echo "$(BRIGHT_BLUE)RECOMMENCE$(DEFAULT)"

.PHONY : clean fclean all 
