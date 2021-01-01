# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexander <alexander@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/27 16:34:05 by kcedra            #+#    #+#              #
#    Updated: 2020/09/25 23:12:18 by alexander        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

SOURCES = ft_memchr.c ft_strlcpy.c ft_memccpy.c ft_strlen.c ft_atoi.c ft_memcpy.c ft_strmapi.c ft_bzero.c ft_memset.c ft_strncmp.c\
ft_calloc.c ft_putchar_fd.c ft_strnstr.c ft_isalnum.c ft_putendl_fd.c ft_strrchr.c ft_isalpha.c ft_putnbr_fd.c ft_strtrim.c\
ft_isascii.c ft_putstr_fd.c ft_substr.c ft_isdigit.c ft_split.c ft_tolower.c ft_isprint.c ft_strchr.c ft_toupper.c ft_itoa.c\
ft_strdup.c ft_strjoin.c ft_strlcat.c ft_memcmp.c ft_memmove.c get_next_line.c get_next_line_utils.c ft_abs.c ft_min_of_2.c

O_FILES = $(SOURCES:.c=.o)

BONUS_SOURCES = ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c ft_lstiter.c\
ft_lstmap.c

BONUS_O_FILES = $(BONUS_SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror

.c.o:	
	gcc $(FLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(O_FILES) $(HEADER)
	ar rcs $(NAME) $(O_FILES)

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

bonus: $(O_FILES) $(BONUS_O_FILES)
	ar rcs $(NAME) $(O_FILES) $(BONUS_O_FILES)

re:	fclean all
