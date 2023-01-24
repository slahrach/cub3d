/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 06:27:00 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 06:48:22 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_config(t_config *config, int ac, char **av)
{
	if (ac != 2)
		ft_handle_error("Need: [map].cub");
	ft_handle_scene_file(config, av[1]);
	textures_array(config);
}

static void	ft_init_player_info(t_config *config, int i, int j)
{
	if (config->map[j][i] == config->orientation)
	{
		config->player->i = (i * SIZE) + (SIZE / 2);
		config->player->j = (j * SIZE) + (SIZE / 2);
		if (config->orientation == 'N')
			config->player->angle = (270);
		else if (config->orientation == 'S')
			config->player->angle = 90;
		else if (config->orientation == 'W')
			config->player->angle = 180;
		else if (config->orientation == 'E')
			config->player->angle = 0;
	}
}

void	ft_player_info(t_config *config)
{
	int	i;
	int	j;

	j = 0;
	while (j < config->map_len)
	{
		i = 0;
		while (i < ft_strlen(config->map[j]))
		{
			ft_init_player_info(config, i, j);
			i++;
		}
		j++;
	}
	config->player->x = 0;
	config->player->y = 0;
}

void	ft_init_player(t_config *config)
{
	ft_player_info(config);
}

t_config	*ft_init(void)
{
	t_config	*game;

	game = malloc(sizeof(t_config));
	game->textures = NULL;
	game->f_color = NULL;
	game->c_color = NULL;
	game->data_mlx = malloc (sizeof (t_data));
	game->player = malloc(sizeof(t_player));
	game->map_len = 0;
	game->orientation = 0;
	game->rays = malloc(sizeof(t_rays *) * X);
	game->walls = malloc(sizeof(t_wall *) * X);
	return (game);
}
