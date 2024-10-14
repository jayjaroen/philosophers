# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 12:58:43 by jjaroens          #+#    #+#              #
#    Updated: 2024/10/14 15:39:09 by jjaroens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c srcs/utils.c srcs/utils_cont.c srcs/parsing.c srcs/init.c \
		srcs/simulation.c srcs/action.c srcs/clean_data.c

INCLUDE = include 

HEADER = $(INCLUDE)/philo.h

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean all

norminette:
	@norminette -R CheckForbiddenSourceHeader srcs/*.c
	@norminette -R CheckDefine $(INCLUDE)/*.h