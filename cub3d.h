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

#ifndef CUB3D_H
# define CUB3D_H
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

# define SIZE 64
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
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_data {
	void		*mlx;
	void		*mlx_win;
	t_img		imgs[4];
	t_img		img;
}	t_data;

typedef struct s_texture
{
	char				*id;
	char				*path;
	struct s_texture	*next;
}	t_texture;

typedef struct s_rays
{
	float	dest;
	float	ray_angle;
	float	x;
	float	y;
}	t_rays;

typedef struct s_wall
{
	int		x1;
	int		x2;
}	t_wall;

typedef struct s_config
{
	t_texture	*textures;
	char		**tex;
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
	int			c;
	int			f;
}	t_config;

t_config		*ft_init(void);
void			free_rays(t_config *config);
void			free_walls(t_config *config);
void			check_angle(t_config *config);
int				ft_check_wall(t_config *config, int deg, int s);
int				ft_check_wall_ray(t_config *config, float xstart, float ystart);
double			deg_to_rad(double x);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_game(t_config *config);
int				e_hook(t_config *config);
int				draw_game_hook(t_config *config);
int				key_hook(int keycode, t_config *config);
int				key_hook2(t_config *config, int deg, int s);
void			ft_init_player(t_config *config);
void			ft_init_config(t_config *config, int ac, char **av);
void			ft_handle_scene_file(t_config *config, char *path);
char			*ft_parse_elements(t_config *config, int fd);
void			ft_check_elements(t_config *config, char *element);
void			ft_parse_map(char *map_, t_config *config);
void			check_surrounding(t_config *config);
int				count_char(char *str, char c);
int				ft_is_color(char **rgb);
void			ft_player_angle(t_player *player);
void			draw_player(t_config *config);
void			ft_addtexture_back(t_texture **head, t_texture *new);
t_texture		*ft_texturenew(char *id, char *path);
void			ft_addtexture_front(t_texture **head, t_texture *new);
int				ft_texturesize(t_texture *lst);
t_texture		*ft_texturelast(t_texture *lst);
int				ft_atoi_(const char *str);
void			ft_strmapi_(char const *s,
					void (*f)(char, t_config *), t_config *config);
void			ft_check_1(char c, t_config	*config);
char			*get_next_line(int fd);
void			ft_raycast(t_config *config);
void			draw_map(t_config *config);
void			ft_textureclear(t_texture **lst);
void			init_imgs(t_config *config);
unsigned int	get_pixel(t_img *image, int x, int y);
void			ft_free_matrix(char **matrix);
unsigned int	rgb_to_hex(char	*color);
int				ft_ray_orientation(t_rays *ray);
void			textures_array(t_config *config);
char			*find_path(char *orient, t_texture *textures);
void			ft_handle_error(char *error);
int				ft_get_matrix_size(char **matrix);
void			ft_free_matrix(char **matrix);
int				ft_check_existing_element(char *id, t_texture *list);

#endif