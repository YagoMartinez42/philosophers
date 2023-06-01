# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samartin <samartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:36:01 by samartin          #+#    #+#              #
#    Updated: 2023/06/01 11:08:23 by samartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -rf
SRC		:=	philosophers.c \
			philo_exit.c \
			philo_lists.c \
			philo_parse.c
OBJ		:= ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} -g3 -fsanitize="address" ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re