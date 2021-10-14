# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 15:34:42 by alexander         #+#    #+#              #
#    Updated: 2021/01/06 23:42:57 by kcedra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = philo_two

HEADER = philo_two.h

FLAGS = -Wall -Werror -Wextra

SOURCES = utils.c main.c threads_utils.c init_funcs.c

O_FILES = $(SOURCES:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o philo_two

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all