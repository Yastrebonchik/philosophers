# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexander <alexander@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 15:19:37 by alexander         #+#    #+#              #
#    Updated: 2020/12/30 15:33:25 by alexander        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = philo_one

HEADER = philo_one.h

FLAGS = -Wall -Werror -Wextra

SOURCES = utils.c main.c

O_FILES = $(SOURCES:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o philo_one

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all