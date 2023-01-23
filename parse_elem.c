/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 06:52:58 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/23 08:50:53 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_parse_more(t_config *config, char *line, int *i, char *map)
{
	char	*line_;

	if (ft_strlen(line) > 1 && *i < 6)
	{
		line_ = ft_substr(line, 0, ft_strlen(line) - 1);
		ft_check_elements(config, line_);
		free(line_);
		(*i)++;
	}
	else if (*i >= 6)
	{
		if (ft_strlen(line) == 1 && *i > 6)
			ft_handle_error("error : empty line inside map");
		if (ft_strlen(line) > 1)
		{
			(*i)++;
			map = ft_strjoin1(map, line);
			(config->map_len)++;
		}
	}
	return (map);
}

char	*ft_parse_elements(t_config *config, int fd)
{
	int		i;
	char	*map;
	char	*line;

	map = NULL;
	line = gnl(fd);
	if (!line)
		ft_handle_error("error : empty map");
	i = 0;
	while (line)
	{
		map = ft_parse_more(config, line, &i, map);
		free(line);
		line = gnl(fd);
	}
	return (map);
}

void	ft_check_elements(t_config *config, char *element)
{
	int			i;
	char		*color;
	char		**expec_textures;
	char		**rgb;
	char		**info;
	int			k;
	t_texture	*new;

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
			if (ft_check_existing_element(info[0], config->textures))
				ft_handle_error("element already exist");
			if (open(info[1], O_RDONLY) < 0)
				ft_handle_error("cant open texture file");
			new = ft_texturenew(info[0], info[1]);
			ft_addtexture_back(&(config->textures), new);
			ft_free_matrix(expec_textures);
			ft_free_matrix(info);
			return ;
		}
		i++;
	}
	ft_free_matrix(expec_textures);
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
			ft_free_matrix(rgb);
			ft_free_matrix(info);
			return ;
		}
		else
		{
			if (config->c_color)
				ft_handle_error("c element already exist");
			config->c_color = color;
			ft_free_matrix(info);
			ft_free_matrix(rgb);
			return ;
		}
	}
	ft_free_matrix(info);
	ft_handle_error("Not a valid element");
}

void	ft_handle_scene_file(t_config *config, char *path)
{
	int		file;
	char	*extension;
	char	*map;

	extension = ft_strchr(path, '.');
	if (extension && !ft_strcmp(extension, ".cub"))
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
