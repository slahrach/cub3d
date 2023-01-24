/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <kessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:45:25 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 03:48:04 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_config *config)
{
	void	*img;
	int		width;
	int		height;

	config->data_mlx->mlx = mlx_init();
	config->data_mlx->mlx_win = mlx_new_window(config->data_mlx->mlx, X, Y,
			"Hello world!");
	config->data_mlx->img.img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->img.addr = mlx_get_data_addr(config->data_mlx->img.img,
			&config->data_mlx->img.bits_per_pixel,
			&config->data_mlx->img.line_length, &config->data_mlx->img.endian);
	init_imgs(config);
}

void	free_rays(t_config *config)
{
	int	i;

	i = 0;
	while (i < X)
	{
		free(config->rays[i]);
		i++;
	}
}

void	free_walls(t_config *config)
{
	int	i;

	i = 0;
	while (i < X)
	{
		free(config->walls[i]);
		i++;
	}
}

void	draw_map(t_config *config)
{
	unsigned int		color;
	int					height;
	int					i;
	int					j;
	int					x_color;
	int					y_color;
	int	ceil = rgb_to_hex(config->c_color);
	int	floor = rgb_to_hex(config->f_color);
	i = 0;
	mlx_clear_window(config->data_mlx->mlx, config->data_mlx->mlx_win);
	config->data_mlx->img.img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->img.addr = mlx_get_data_addr(config->data_mlx->img.img, &config->data_mlx->img.bits_per_pixel, &config->data_mlx->img.line_length,&config->data_mlx->img.endian);
	while (i < X)
	{
		if ((int)config->rays[i]->x % 28 == 0 || (int)config->rays[i]->x % 28 == 27)
			x_color = (int)config->rays[i]->y % 28;
		else
			x_color = (int)config->rays[i]->x % 28;
		j = 0;
		while(j < Y)
		{
			if (j < config->walls[i]->x1)
				my_mlx_pixel_put(config->data_mlx,i, j, ceil);
			else if (j >= config->walls[i]->x1 && j < config->walls[i]->x2)
			{
				height = config->walls[i]->x2 - config->walls[i]->x1;
				y_color = ((j + height / 2) - 400) * ((float)28 / (height));
				color = get_pixel(&config->data_mlx->imgs[ft_ray_orientation(config->rays[i])], x_color, y_color);
				if (x_color == 63)
					my_mlx_pixel_put(config->data_mlx,i,j,0xff0000);
				else
					my_mlx_pixel_put(config->data_mlx,i,j,color);
			}
			else
				my_mlx_pixel_put(config->data_mlx,i,j, floor);
			j++;
		}
		i++;
	}
}

void	ft_raycast(t_config *config)
{
	init_window(config);
	draw_player(config);
	draw_game(config);
	mlx_key_hook(config->data_mlx->mlx_win, key_hook, config);
	mlx_hook(config->data_mlx->mlx_win, 17, 0, e_hook, config);
	mlx_loop_hook(config->data_mlx->mlx, draw_game_hook, config);
	mlx_loop(config->data_mlx->mlx);
}
