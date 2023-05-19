# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samartin <samartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:36:01 by samartin          #+#    #+#              #
#    Updated: 2023/05/19 12:21:43 by samartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -rf
SRC		:=	philosophers.c \
			philo_exit.c
OBJ		:= ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re