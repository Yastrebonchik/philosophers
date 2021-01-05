# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 15:19:37 by alexander         #+#    #+#              #
#    Updated: 2021/01/05 16:07:02 by kcedra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = philo_one

HEADER = philo_one.h

FLAGS = -Wall -Werror -Wextra

SOURCES = utils.c main.c init_funcs.c threads_utils.c

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