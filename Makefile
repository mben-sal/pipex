# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 15:22:31 by mben-sal          #+#    #+#              #
#    Updated: 2023/01/11 17:50:49 by mben-sal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =   pipex

HEADER = pipex.h

SRC = ./ft_split.c\
	  ./ft_strjoin.c\
	  ./main.c\
	  ./ft_child.c\
	  ./ft_printf.c\
	  ./utils.c
		

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra
CC = gcc


all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all