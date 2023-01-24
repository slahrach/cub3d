/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <kessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:21:16 by kessalih          #+#    #+#             */
/*   Updated: 2023/01/24 04:06:54 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		i;

	i = (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	dst = data->img.addr + i;
	*(unsigned int *)dst = color;
}

int	key_hook2(t_config *config, int deg, int s)
{
	config->player->x = 0;
	config->player->y = 0;
	if (ft_check_wall(config, deg, s) == 0)
		return (0);
	config->player->x = cos(deg_to_rad(config->player->angle + deg)) * s;
	config->player->y = sin(deg_to_rad(config->player->angle + deg)) * s;
	return (1);
}

int	key_hook(int keycode, t_config *config)
{
	if (keycode == 2 && key_hook2(config, 90, 1) == 0)
		return (keycode);
	else if (keycode == 0 && key_hook2(config, 90, -1) == 0)
		return (keycode);
	else if (keycode == 13 && key_hook2(config, 0, 1) == 0)
		return (keycode);
	else if (keycode == 1 && key_hook2(config, 0, -1) == 0)
		return (keycode);
	else if (keycode == 124)
	{
		config->player->angle = config->player->angle + 10;
		config->player->x = 0;
		config->player->y = 0;
	}
	else if (keycode == 123)
	{
		config->player->angle = config->player->angle - 10;
		config->player->x = 0;
		config->player->y = 0;
	}
	else if (keycode == 53)
		e_hook(config);
	check_angle(config);
	draw_player(config);
	return (keycode);
}

int	draw_game_hook(t_config *config)
{
	ft_player_angle(config->player);
	free_rays(config);
	free_walls(config);
	draw_game(config);
	return (0);
}

int	e_hook(t_config *config)
{
	mlx_clear_window(config->data_mlx->mlx, config->data_mlx->mlx_win);
	exit(0);
}
