/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 04:26:46 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 04:27:36 by slahrach         ###   ########.fr       */
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