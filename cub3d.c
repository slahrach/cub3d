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
	printf("Error: %s\n", error);
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
		atoi = ft_atoi_(rgb[i]);
		if (atoi < 0 || atoi > 255)
			return (0);
		if (!atoi && ft_strcmp(rgb[i], "0"))
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_elements(t_config *config, char *element)
{
	int			i;
	char		**expec_textures;
	char		**rgb;
	char		**info;
	t_texture	*new;

	i = 0;
	expec_textures = ft_split("NO SO EA WE", ' ');
	info = ft_split(element, ' ');
	if (ft_get_matrix_size(info) != 2)
		ft_handle_error("Elements error : too many info");
	while (expec_textures[i])
	{
		if (!ft_strcmp(expec_textures[i], info[0]))
		{
			if(ft_check_existing_element(info[0], config->textures))
				ft_handle_error("Elements error : element already exist");
			if (open(info[1], O_RDONLY) < 0)
				ft_handle_error("Elements error : cant open texture file");
			new = ft_texturenew(info[0], info[1]);
			ft_addtexture_back(&(config->textures), new);
			ft_free_matrix(expec_textures);
			return ;
		}
		i++;
	}
	if (!ft_strcmp(info[0], "C") || !ft_strcmp(info[0], "F"))
	{
		rgb = ft_split(info[1], ',');
		if (!ft_is_color(rgb))
			ft_handle_error("Elements error : Not a valid color");
		if (!ft_strcmp(info[0], "F"))
		{
			if (config->f_color)
				ft_handle_error("Elements error : f element already exist");
			config->f_color = info[1];
			ft_free_matrix(expec_textures);
			ft_free_matrix(rgb);
			return ;
		}
		else
		{
			if (config->c_color)
				ft_handle_error("Elements error : c element already exist");
			config->c_color = info[1];
			ft_free_matrix(expec_textures);
			ft_free_matrix(rgb);
			return ;
		}
	}
	ft_handle_error("Elements error : Not a valid element");
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
		if (i == 6)
			ft_check_missing_elements(config);
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
int	ft_no_spaces_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	return (len);
}
void	ft_remove_spaces(t_config *config, char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	config->map = malloc((config->map_len + 1) * sizeof(char *));
	while (map[i])
	{
		config->map[i] = malloc(ft_no_spaces_len(map[i]) + 1);
		j = 0;
		k = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ')
			{
				config->map[i][k] = map[i][j];
				k++;
			}
			j++;
		}
		config->map[i][k] = '\0';
		i++;
	}
	config->map[i] = NULL;
	ft_free_matrix(map);
}
void	ft_parse_map(char *map_, t_config *config)
{
	char	**map;
	int		i;

	i = 0;
	map = ft_split(map_, '\n');
	free(map_);
	ft_strmapi_(map[0], ft_check_1, config);
	ft_strmapi_(map[config->map_len - 1], ft_check_1, config);
	while(map[i])
	{
		ft_strmapi_(map[i], ft_check_chars, config);
		i++;
	}
	ft_remove_spaces(config, map);
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
	}
	else
		ft_handle_error("Map error: has to be .cub");
}

void ft_init_config (t_config *config, int ac, char **av)
{
	if (ac < 2)
		ft_handle_error("Need: [map].cub");
	ft_handle_scene_file(config, av[1]);
}

t_config	*ft_init()
{
	t_config *game;

	game = malloc(sizeof(t_config));
	game->textures = NULL;
	game->f_color = NULL;
	game->c_color = NULL;
	game->data_mlx = malloc (sizeof (t_data *));
	game->map_len = 0;
	game->orientation = 0;
	game->r = M_PI_2;
	game->player = malloc(sizeof(t_player));
	game->rays = malloc(sizeof(t_rays *) * X);
	game->walls = malloc(sizeof(t_wall *) * X);
	return (game);
}

void	ft_player_info(t_config *config)
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
				config->player->i = (i * SIZE) + (SIZE / 2);
				config->player->j = (j * SIZE) + (SIZE / 2);
				printf("%d %d sss\n",config->player->i,config->player->j);
				if (config->orientation == 'N')
					config->player->angle = (270);
				else if (config->orientation == 'S')
					config->player->angle = 90;
				else if (config->orientation == 'W')
					config->player->angle = 180;
				else if (config->orientation == 'E')
					config->player->angle = 0;
			}
			i++;
		}
		j++;
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

void	ft_init_player(t_config *config)
{
	ft_player_info(config);
	ft_player_angle(config->player);
}
int	main(int argc, char** argv)
{
	t_config *game;

	game = ft_init();
	ft_init_config(game, argc, argv);
	ft_init_player(game);
	ft_raycast(game);
}