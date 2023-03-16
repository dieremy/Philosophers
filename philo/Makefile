# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:41:08 by robegarc          #+#    #+#              #
#    Updated: 2023/03/16 17:44:42 by robegarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c utils.c
OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -pthread -Wall -Werror -Wextra -g
NAME = philo

.o: .c
	$(CC) $(FLAGS) -I $(SRC) -c $< -o $(NAME)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean fclean all 