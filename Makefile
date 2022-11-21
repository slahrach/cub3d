# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/06 19:47:07 by slahrach          #+#    #+#              #
#    Updated: 2022/11/21 11:37:52 by slahrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub

LIB = libft/libft.a

LIBFT = ./libft

SRCS =  cub3d.c gnl.c gnl_utils.c utils.c

CFLAGS = -Wall -Wextra -Werror

CLINKS = -lmlx -framework OpenGL -framework AppKit

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	Make -C ${LIBFT}
	${CC} -o ${NAME} ${OBJS} ${LIB}

clean :
	Make clean -C ${LIBFT}
	rm -f ${OBJS}

fclean : clean
	Make fclean -C ${LIBFT}
	rm -f ${NAME}

re : fclean all

%.o : %.c
	${CC} -c $<

.PHONY: clean all fclean re bonus