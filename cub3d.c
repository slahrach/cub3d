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
			return ;
		}
		i++;
	}
	if (!ft_strcmp(info[0], "C") || !ft_strcmp(info[0], "F"))
	{
		rgb = ft_split(info[1], ',');
		if (!ft_is_color(rgb))
			ft_handle_error("Elements error : Not a valid color");
		if (!ft_strcmp(info[0], "C"))
		{
			if (config->c_color)
				ft_handle_error("Elements error : element already exist");
			config->c_color = info[1];
		}
		else
		{
			if (config->f_color)
				ft_handle_error("Elements error : element already exist");
			config->f_color = info[1];
		}
		return ;
	}
	ft_handle_error("Elements error : Not a valid element");
}

void ft_parse_map(t_config *config, int fd)
{
	int 	i;
	int		valid;
	char	*line;
	char	*line_;

	line = gnl(fd);
	if (!line)
		ft_handle_error("error : empty map");
	i = 0;
	valid = 0;
	while (line)
	{
		line_ = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		if (*line_ && i < 6)
		{
			printf("%d\n", i);
			ft_check_elements(config, line_);
			i++;
		}
		if (i == 6)
			ft_check_missing_elements(config);
		line = gnl(fd);
	}
}

void ft_handle_scene_file(t_config *config, char *path)
{
	int	 file;
	char	*extension;

	extension = ft_strchr(path, '.');
	if (extension && !ft_strcmp(extension , ".cub"))
	{
		file = open(path, O_RDONLY);
		if (file < 0) 
			ft_handle_error("Map error: file not found.");
		ft_parse_map(config, file);
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

t_config *ft_allocate(void)
{
	t_config	*game;

	game = malloc(sizeof(t_config *));
	game->textures = NULL;
	game->c_color = NULL;
	game->f_color = NULL;
	return (game);
}

int	main(int argc, char** argv)
{
	t_config *game;

	game = ft_allocate();
	ft_init_config(game, argc, argv);
	//ft_raycast();
}