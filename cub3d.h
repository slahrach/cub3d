/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:46:01 by slahrach          #+#    #+#             */
/*   Updated: 2022/11/21 12:15:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUBE3D_H
# define CUBE3D_H
# include "libft/libft.h"
# include "gnl.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# define MAP_SIZE 200


typedef struct s_texture
{
    char            *id;
    char            *path;
    struct s_texture *next;
} t_texture;

typedef struct s_config
{
    t_texture	*textures;
    char        *f_color;
    char        *c_color;
} t_config;

void			ft_addtexture_back(t_texture **head, t_texture *new);
t_texture		*ft_texturenew(char *id, char *path);
void			ft_addtexture_front(t_texture **head, t_texture *new);
int				ft_texturesize(t_texture *lst);
t_texture		*ft_texturelast(t_texture *lst);
int         	ft_atoi_(const char *str);
// int              ft_raycast (void);
char	        *get_next_line(int fd);


#endif