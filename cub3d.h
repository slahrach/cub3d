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

# define SIZE 28
# define P_SIZE 1
# define X 1200
# define Y 800
# define N 0
# define S 1
# define E 2
# define W 3

typedef struct s_player
{
    float	x;
    float	y;
	float	i;
	float	j;
	int		top;
	int		left;
	double	angle;
} t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
} t_img;

typedef struct	s_data {
    void		*mlx;
	void		*mlx_win;
	t_img		imgs[4];
	t_img		img;
}				t_data;

typedef struct s_texture
{
	char			*id;
	char			*path;
	struct s_texture *next;
} t_texture;

typedef	struct s_rays
{
	float	dest;
	float	ray_angle;
	float	x;
	float	y;
} t_rays;


typedef struct s_wall
{
	int	x1;
	int	x2;
} t_wall;

typedef struct s_config
{
	t_texture	*textures;
	char		**tex;
	double		r;
	double		ray_angle;
	char		*c_color;
	char		*f_color;
	int			map_len;
	int			map_width;
	int			wall_h;
	char		orientation;
	char		**map;
	t_data		*data_mlx;
	t_player	*player;
	t_rays		**rays;
	t_wall		**walls;
} t_config;

void			ft_player_angle(t_player *player);
void			draw_player(t_config *config);
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
void			draw_map(t_config *config);
void			ft_textureclear(t_texture **lst);
void			init_imgs(t_config *config);
unsigned int	get_pixel(t_img *image, int x, int y);
void			ft_free_matrix(char **matrix);
unsigned int	rgb_to_hex(char	*color);
int				ft_ray_orientation(t_rays *ray);

#endif