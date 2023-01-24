/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:45:25 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 06:42:42 by slahrach         ###   ########.fr       */
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
			"cub3D");
	config->data_mlx->img.img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->img.addr = mlx_get_data_addr(config->data_mlx->img.img,
			&config->data_mlx->img.bits_per_pixel,
			&config->data_mlx->img.line_length, &config->data_mlx->img.endian);
	init_imgs(config);
}

void	draw_strip(int i, int j, t_config *config, int x_color)
{
	int	color;
	int	img_i;
	int	y_color;
	int	height;


	if (j < config->walls[i]->x1)
		my_mlx_pixel_put(config->data_mlx, i, j, config->c);
	else if (j >= config->walls[i]->x1 && j < config->walls[i]->x2)
	{
		height = config->walls[i]->x2 - config->walls[i]->x1;
		y_color = (j - config->walls[i]->x1) * ((float)64 / (height));
		img_i = ft_ray_orientation(config->rays[i]);
		color = get_pixel(&config->data_mlx->imgs[img_i], x_color, y_color);
		my_mlx_pixel_put(config->data_mlx, i, j, color);
	}
	else
		my_mlx_pixel_put(config->data_mlx, i, j, config->f);
}

static void	draw_walls(t_config *config)
{
	int	i;
	int	j;
	int	x_color;

	i = 0;
	while (i < X)
	{
		if ((int)config->rays[i]->x % SIZE == 0
			|| (int)config->rays[i]->x % SIZE == SIZE - 1)
			x_color = (int)config->rays[i]->y % SIZE;
		else
			x_color = (int)config->rays[i]->x % SIZE;
		j = 0;
		while (j < Y)
		{
			draw_strip(i, j, config, x_color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_config *config)
{
	unsigned int	color;
	int				height;
	int				ceil;
	int				floor;

	config->c = rgb_to_hex(config->c_color);
	config->f = rgb_to_hex(config->f_color);
	mlx_clear_window(config->data_mlx->mlx, config->data_mlx->mlx_win);
	config->data_mlx->img.img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->img.addr = mlx_get_data_addr(config->data_mlx->img.img,
			&config->data_mlx->img.bits_per_pixel,
			&config->data_mlx->img.line_length,
			&config->data_mlx->img.endian);
	draw_walls(config);
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
