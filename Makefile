# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 12:58:43 by jjaroens          #+#    #+#              #
#    Updated: 2024/07/06 15:12:17 by jjaroens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c srcs/utils.c

INCLUDE = include 

HEADER = $(INCLUDE)/philo.h

OBJS = $(SRCS: .c=.o)

CC = cc 

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CLAGS) -I$(INCLUDE) $(OBJS) -o$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

norminette:
	@norminette -R CheckForbiddenSourceHeader srcs/*.c
	@norminette -R CheckDefine $(INCLUDE)/*.h