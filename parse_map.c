/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:40:19 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 07:12:27 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_1(char c, t_config *config)
{
	if (c != '1' && c != ' ')
	{
		config->c = 0;
		ft_handle_error("Map must be surrounded by walls");
	}
}

void	ft_check_chars(char c, t_config *config)
{
	if (c != '1' && c != ' ' && c != '0'
		&& c != 'W' && c != 'N' && c != 'E' && c != 'S')
		ft_handle_error("Imposter : unrecognized character");
	if (c == 'W' || c == 'N' || c == 'E' || c == 'S')
	{
		if (config->orientation)
			ft_handle_error("orientation character already exist");
		config->orientation = c;
	}
}

void	check_surrounding(t_config *config)
{
	int		i;
	size_t	j;

	i = -1;
	while (config->map[++i])
	{
		j = -1;
		while (config->map[i][++j])
		{
			if (config->map[i][j] == '0'
				|| config->map[i][j] == config->orientation)
			{
				if ((i > 0 && j >= ft_strlen(config->map[i - 1]) - 1)
					|| (config->map[i - 1][j + 1] == ' ')
					|| (config->map[i - 1][j - 1] == ' '))
					ft_handle_error("map not surrounded by walls");
				if (((i < config->map_len - 1)
						&& j >= ft_strlen(config->map[i + 1]) - 1)
					|| (config->map[i + 1][j + 1] == ' ')
					|| (config->map[i + 1][j - 1] == ' '))
					ft_handle_error("map not surrounded by walls");
			}
		}
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
	while (config->map[i])
	{
		ft_strmapi_(config->map[i], ft_check_chars, config);
		i++;
	}
	check_surrounding(config);
}
