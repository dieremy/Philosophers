# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:41:08 by robegarc          #+#    #+#              #
#    Updated: 2023/03/24 10:02:09 by robegarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BRIGHT_BLUE=\033[4;94m
MAGENTA=\033[4;35m
DEFAULT=\033[0m

SRC = start.c main.c utils.c check_state.c
OBJ = $(SRC:.c=.o)
CC = gcc -g
FLAGS = -pthread -Wall -Werror -Wextra
NAME = philo

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ 

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(BRIGHT_BLUE)./$(NAME) CREATION$(DEFAULT)"

all: $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "$(MAGENTA)objs DELETION$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(MAGENTA)./$(NAME) DELETION, CLEAN & PERFUMED$(DEFAULT)"

re: fclean all
	@echo "$(BRIGHT_BLUE)RECOMMENCE$(DEFAULT)"

.PHONY : clean fclean all 
