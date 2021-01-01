# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexander <alexander@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 15:34:11 by alexander         #+#    #+#              #
#    Updated: 2020/12/30 15:35:18 by alexander        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = philo_three

HEADER = philo_three.h

FLAGS = -Wall -Werror -Wextra

SOURCES = utils.c main.c

O_FILES = $(SOURCES:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o philo_three

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all