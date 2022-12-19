/* ************************************************************************** */
/*								                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:46:01 by slahrach          #+#    #+#             */
/*   Updated: 2022/11/30 00:02:55 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUBE3D_H
# define CUBE3D_H
# include "libft/libft.h"
# include <mlx.h>
# include "gnl.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

typedef struct s_player
{
    int x;
    int y;
} t_player;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    void	*mlx;
	void	*mlx_win;
}	t_data;

typedef struct s_texture
{
	char			*id;
	char			*path;
	struct s_texture *next;
} t_texture;

typedef struct s_config
{
	t_texture	*textures;
	double		r;
	char		*c_color;
	char		*f_color;
	int			map_len;
	int			map_width;
	char		orientation;
	char		**map;
	t_data		*data_mlx;
	int			px;
	int			py;
} t_config;

void			ft_addtexture_back(t_texture **head, t_texture *new);
t_texture		*ft_texturenew(char *id, char *path);
void			ft_addtexture_front(t_texture **head, t_texture *new);
int				ft_texturesize(t_texture *lst);
t_texture		*ft_texturelast(t_texture *lst);
int		 		ft_atoi_(const char *str);
void			ft_strmapi_(char const *s, void (*f)(char, t_config *), t_config *config);
void			ft_check_1(char c, t_config* config);
char			*get_next_line(int fd);
void			ft_raycast(t_config *config);


#endif