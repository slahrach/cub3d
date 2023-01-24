# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/06 19:47:07 by slahrach          #+#    #+#              #
#    Updated: 2023/01/24 07:06:28 by slahrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

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
	@ ${CC} ${CFLAGS} ${OBJS} ${LIB} ${CLINKS} -o ${NAME}
	@ echo "cub3D ready"

clean :
	Make clean -C ${LIBFT}
	@rm -f ${OBJS}
	@ echo "obj files removed"

fclean : clean
	Make fclean -C ${LIBFT}
	@rm -f ${NAME}
	@ echo "executable removed"

re : fclean all

%.o : %.c
	@ ${CC} ${CFLAGS} -Imlx -c $<

.PHONY: clean all fclean re bonus