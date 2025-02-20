# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 22:16:38 by sacgarci          #+#    #+#              #
#    Updated: 2025/02/20 01:36:02 by sacgarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

CFILES = checks.c errors_n_free.c main.c parsing.c philo.c utils.c routine.c

OFILES = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

re : fclean all

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OFILES)

.PHONY = all fclean clean re
