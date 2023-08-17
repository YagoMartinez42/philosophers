# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samartin <samartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:36:01 by samartin          #+#    #+#              #
#    Updated: 2023/08/17 11:42:29 by samartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -rf
SRC		:=	philosophers.c \
			philo_actions.c \
			philo_exit.c \
			philo_lists.c \
			philo_msgs.c \
			philo_parse.c \
			philo_time.c \
			philo_exception_case.c
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