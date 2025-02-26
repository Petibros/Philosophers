# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 08:09:02 by sacgarci          #+#    #+#              #
#    Updated: 2025/02/26 08:13:40 by sacgarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = check.c check_main.c errors_n_free.c main.c parsing.c philo.c \
		 process_gestion.c routine.c utils.c
OFILES = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

fclean : clean
	rm $(NAME)

clean :
	rm $(OFILES)

re : fclean all

.PHONY = all re clean fclean
