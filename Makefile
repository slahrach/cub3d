# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kessalih <kessalih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/06 19:47:07 by slahrach          #+#    #+#              #
#    Updated: 2023/01/23 02:38:10 by kessalih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub

LIB = libft/libft.a

LIBFT = ./libft

SRCS =  cub3d.c gnl.c gnl_utils.c utils.c two_d.c

CFLAGS = -Wall -Wextra -Werror

CLINKS = -lmlx -framework OpenGL -framework AppKit

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	Make -C ${LIBFT}
	${CC} ${OBJS} ${LIB} -lmlx -framework OpenGL -framework AppKit -o ${NAME}

clean :
	Make clean -C ${LIBFT}
	rm -f ${OBJS}

fclean : clean
	Make fclean -C ${LIBFT}
	rm -f ${NAME}

re : fclean all

%.o : %.c
	${CC}  -Imlx -c $<

.PHONY: clean all fclean re bonus