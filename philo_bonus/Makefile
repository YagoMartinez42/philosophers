# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samartin <samartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:48:14 by samartin          #+#    #+#              #
#    Updated: 2023/05/18 12:48:17 by samartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo_bonus
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -rf
SRC		:=
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