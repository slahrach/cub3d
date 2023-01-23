/* ************************************************************************** */
/*									                                        */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:45:47 by slahrach          #+#    #+#             */
/*   Updated: 2022/11/21 12:16:39 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_handle_error(char *error)
{
	printf("Error\n%s\n", error);
	exit(1);
}
int	ft_check_existing_element(char *id, t_texture* list)
{
	while(list)
	{
		if (!ft_strcmp(id, list->id))
			return (1);
		list = list->next;
	}
	return (0);
}
void ft_check_missing_elements(t_config *config)
{
	if(!(config->c_color && config->f_color && ft_texturesize(config->textures) == 4))
		ft_handle_error("missing Element");
}

void	ft_free_matrix(char **matrix)
{
	int	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int ft_get_matrix_size(char **matrix)
{
	int i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

int ft_is_color(char **rgb)
{
	int i;
	int atoi;

	i = 0;
	if (ft_get_matrix_size(rgb) != 3)
		return (0);
	while (rgb[i])
	{
		if (rgb[i][0] == '+')
			atoi = ft_atoi_(rgb[i] + 1);
		else
			atoi = ft_atoi_(rgb[i]);
		if (atoi < 0 || atoi > 255)
			return (0);
		if (!atoi && ft_strcmp(rgb[i], "0"))
			return (0);
		i++;
	}
	return (1);
}
int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
void	ft_check_elements(t_config *config, char *element)
{
	int			i;
	char		*color;
	char		**expec_textures;
	char		**rgb;
	char		**info;
	t_texture	*new;
	int			k;

	i = 0;
	expec_textures = ft_split("NO SO EA WE", ' ');
	info = ft_split(element, ' ');
	if (!ft_strchr(element, ',') && ft_get_matrix_size(info) != 2)
		ft_handle_error("more or less info");
	if ((ft_strchr(element, ',') && count_char(element, ',') != 2))
		ft_handle_error("extra or missing comma");
	while (expec_textures[i])
	{
		if (!ft_strcmp(expec_textures[i], info[0]))
		{
			if(ft_check_existing_element(info[0], config->textures))
				ft_handle_error("element already exist");
			if (open(info[1], O_RDONLY) < 0)
				ft_handle_error("cant open texture file");
			new = ft_texturenew(info[0], info[1]);
			ft_addtexture_back(&(config->textures), new);
			ft_free_matrix(expec_textures);
			return ;
		}
		i++;
	}
	if (!ft_strcmp(info[0], "C") || !ft_strcmp(info[0], "F"))
	{
		k = 1;
		color = NULL;
		while (k < ft_get_matrix_size(info))
		{
			color = ft_strjoin1(color, info[k]);
			k++;
		}
		rgb = ft_split(color, ',');
		if (!ft_is_color(rgb))
			ft_handle_error("Not a valid color");
		if (!ft_strcmp(info[0], "F"))
		{
			if (config->f_color)
				ft_handle_error("f element already exist");
			config->f_color = color;
			ft_free_matrix(expec_textures);
			ft_free_matrix(rgb);
			return ;
		}
		else
		{
			if (config->c_color)
				ft_handle_error("c element already exist");
			config->c_color = color;
			ft_free_matrix(expec_textures);
			ft_free_matrix(rgb);
			return ;
		}
	}
	ft_handle_error("Not a valid element");
}

char *ft_parse_elements(t_config *config, int fd)
{
	int 	i;
	char	*map;
	char	*line;
	char	*line_;

	map = NULL;
	line = gnl(fd);
	if (!line)
		ft_handle_error("error : empty map");
	i = 0;
	while (line)
	{
		if (ft_strlen(line) > 1 && i < 6)
		{
			line_ = ft_substr(line, 0, ft_strlen(line) - 1);
			free(line);
			ft_check_elements(config, line_);
			i++;
		}
		else if (i >= 6)
		{
			if (ft_strlen(line) == 1 && i > 6)
				ft_handle_error("error : empty line inside map");
			if (ft_strlen(line) > 1)
			{
				i++;
				map = ft_strjoin(map, line);
				(config->map_len)++;
			}
		}
		line = gnl(fd);
	}
	return (map);
}

void	ft_check_1(char c, t_config *config)
{
	if (c != '1' && c != ' ')
		ft_handle_error("Map must be surrounded by walls");
}

void	ft_check_chars(char c, t_config *config)
{
	if (c != '1' && c != ' ' && c != '0' && c != 'W' && c != 'N' && c != 'E' && c != 'S')
		ft_handle_error("Imposter : unrecognized character");
	if (c == 'W' || c == 'N' || c == 'E' || c == 'S')
	{
		if (config->orientation)
			ft_handle_error("orientation character already exist");
		config->orientation = c;
	}
}
int	ft_get_width(t_config *config)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(config->map[0]);
	while (config->map[i])
	{
		if (ft_strlen(config->map[i]) > len)
			len = ft_strlen(config->map[i]);
		i++;
	}
	return (len);
}

void	check_surrounding(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == '0' || config->map[i][j] == config->orientation)
			{
				if ((i > 0 && j >= ft_strlen(config->map[i - 1])) 
					|| (config->map[i - 1][j + 1] == ' '))
					ft_handle_error("map not surrounded by walls");
				if (((i < config->map_len - 1) && j >= ft_strlen(config->map[i + 1]))
					|| (config->map[i + 1][j + 1] == ' '))
						ft_handle_error("map not surrounded by walls");
			}
			j++;
		}
		i++;
	}
}

void	ft_parse_map(char *map_, t_config *config)
{
	int		i;

	i = 0;
	config->map = ft_split(map_, '\n');
	free(map_);
	ft_strmapi_(config->map[0], ft_check_1, config);
	ft_strmapi_(config->map[config->map_len - 1], ft_check_1, config);
	while(config->map[i])
	{
		ft_strmapi_(config->map[i], ft_check_chars, config);
		i++;
	}
	check_surrounding(config);
}

char	*find_path(char *orient, t_texture *textures)
{
	while(textures)
	{
		if (!ft_strcmp(textures->id, orient))
			return (ft_strdup(textures->path));
		textures = textures->next;
	}
	return (NULL);
}
void	textures_array(t_config *config)
{
	config->tex = malloc(5 * sizeof(char *));
	config->tex[N] = find_path("NO", config->textures);
	config->tex[S] = find_path("SO", config->textures);
	config->tex[E] = find_path("EA", config->textures);
	config->tex[W] = find_path("WE", config->textures);
	config->tex[4] = NULL;
	ft_textureclear(&config->textures);
}

void ft_handle_scene_file(t_config *config, char *path)
{
	int		file;
	char	*extension;
	char	*map;

	extension = ft_strchr(path, '.');
	if (extension && !ft_strcmp(extension , ".cub"))
	{
		file = open(path, O_RDONLY);
		if (file < 0) 
			ft_handle_error("Map error: file not found.");
		map = ft_parse_elements(config, file);
		if (!map)
			ft_handle_error("Map is Missing");
		ft_parse_map(map, config);
		if (!config->orientation)
			ft_handle_error("...");
	}
	else
		ft_handle_error("Map error: has to be .cub");
}

unsigned int	get_pixel(t_img *image, int x, int y)
{
	char	*dst;

	//printf("%s\n",	image->addr);
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	init_imgs(t_config *config)
{
	int	i;

	//config->data_mlx->imgs = malloc (4 * sizeof (t_img));
	i = 0;
	while (i < 4)
	{
		config->data_mlx->imgs[i].img = mlx_xpm_file_to_image(config->data_mlx->mlx, config->tex[i], &config->data_mlx->imgs[i].width, &config->data_mlx->imgs[i].height);
		config->data_mlx->imgs[i].addr = mlx_get_data_addr(config->data_mlx->imgs[i].img, &config->data_mlx->imgs[i].bits_per_pixel, &config->data_mlx->imgs[i].line_length, &config->data_mlx->imgs[i].endian);
		i++;
	}
}

void ft_init_config (t_config *config, int ac, char **av)
{
	if (ac < 2)
		ft_handle_error("Need: [map].cub");
	ft_handle_scene_file(config, av[1]);
	textures_array(config);
}

t_config	*ft_init()
{
	t_config *game;

	game = malloc(sizeof(t_config));
	game->textures = NULL;
	game->f_color = NULL;
	game->c_color = NULL;
	game->data_mlx = malloc (sizeof (t_data));
	game->map_len = 0;
	game->orientation = 0;
	game->r = M_PI_2;
	game->rays = malloc(sizeof(t_rays *) * X);
	game->walls = malloc(sizeof(t_wall *) * X);
	return (game);
}

void	ft_player_info(t_player *player, t_config *config)
{
	int	i;
	int	j;

	j = 0;
	while (j < config->map_len)
	{
		i = 0;
		while(i < ft_strlen(config->map[j]))
		{
			if(config->map[j][i] == config->orientation)
			{
				player->i = (i * SIZE) + (SIZE / 2);
				player->j = (j * SIZE) + (SIZE / 2);
				printf("adasda\n");
				printf("%f  %f sss\n",player->i,player->j);
				if (config->orientation == 'N')
					player->angle = (270);
				else if (config->orientation == 'S')
					player->angle = 90;
				else if (config->orientation == 'W')
					player->angle = 180;
				else if (config->orientation == 'E')
					player->angle = 0;
			}
			i++;
		}
		j++;
	}
	player->x = 0;
	player->y = 0;
}

int	ft_ray_orientation(t_rays *ray)
{
	if (ray->ray_angle >= 0 && ray->ray_angle <= 180)
	{
		if ((int)ray->y % 28 == 0 || (int)ray->y % 28 == 27)
			return (0);
		else
		{
			if (ray->ray_angle >= 0 && ray->ray_angle < 90)
				return (2);
			else
				return (3);
		}
	}
	else
	{
		if ((int)ray->y % 28 == 0 || (int)ray->y % 28 == 27)
			return (1);
		else
		{
			if (ray->ray_angle > 180 && ray->ray_angle < 270)
				return (3);
			else
				return (2);
		}
	}
}
void	ft_player_angle(t_player *player)
{
	if (player->angle > 270 || player->angle < 90)
		player->left = -1;
	else
		player->left = 1;
	if (player->angle > 0 && player->angle < 180)
		player->top = -1;
	else
		player->top = 1;
}

t_player	*ft_init_player(t_config *config)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	ft_player_info(player, config);
	ft_player_angle(player);
	return (player);
}
int	main(int argc, char** argv)
{
	int	i;
	t_config *game;

	game = ft_init();
	ft_init_config(game, argc, argv);
	game->player = ft_init_player(game);
	i = 0;
	// while (game->tex[i])
	// {
	// 	printf("%s\n", game->tex[i]);
	// 	i++;
	// }
	//printf("%f %f aaa\n",game->player->i, game->player->j);
	ft_raycast(game);
}