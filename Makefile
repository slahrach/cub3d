# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/06 19:47:07 by slahrach          #+#    #+#              #
#    Updated: 2023/01/24 06:04:03 by slahrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub

LIB = libft/libft.a

LIBFT = ./libft

SRCS =  cub3d.c gnl.c gnl_utils.c lists_utils.c utils1.c utils2.c \
		two_d.c init.c parse_elem.c parse_map.c textures_utils.c \
		draw.c hook.c check.c parse.c draw_utils.c

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