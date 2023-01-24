/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:19:22 by kessalih          #+#    #+#             */
/*   Updated: 2023/01/24 06:40:35 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_config *config)
{
	config->player->j = config->player->j + config->player->y * 4.0;
	config->player->i = config->player->i + config->player->x * 4.0;
}

void	draw_square(int i, int j, int x, t_config *config)
{
	int	t1;
	int	t2;

	t1 = j * x;
	while (t1 <= x * (j + 1))
	{
		t2 = i * x;
		while (t2 <= x * (i + 1))
		{	
			if (config->map[j][i] == '1')
				my_mlx_pixel_put(config->data_mlx, t2, t1, 0xFFFFFF);
			else
				my_mlx_pixel_put(config->data_mlx, t2, t1, 0x000000);
			t2++;
		}
		t1++;
	}
}

void	draw_minimap(t_config *config)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = SIZE;
	while (config->map[j])
	{
		i = 0;
		x = SIZE;
		while (config->map[j][i])
		{
			draw_square(i, j, SIZE, config);
			i++;
			x = x + SIZE;
		}
		j++;
	}
}

float	render_ray(t_config *config, int c)
{
	float	x;
	float	xp;
	float	y;
	float	yp;
	int		i;

	x = config->player->i + cos(deg_to_rad(config->player->angle));
	xp = config->player->i + cos(deg_to_rad(config->player->angle));
	y = config->player->j + sin(deg_to_rad(config->player->angle));
	yp = config->player->j + sin(deg_to_rad(config->player->angle));
	i = 0;
	while (ft_check_wall_ray(config, x, y))
	{
		y += sin(deg_to_rad(config->ray_angle)) / 16;
		x += cos(deg_to_rad(config->ray_angle)) / 16;
		i++;
	}
	config->rays[c]->x = x;
	config->rays[c]->y = y;
	return (sqrt(((x - xp) * (x - xp)) + ((y - yp) * (y - yp))));
}

void	draw_game(t_config *config)
{
	int		x;
	int		y;
	float	f;
	float	angle;

	x = 0;
	y = config->map_len * SIZE;
	config->ray_angle = config->player->angle - 30;
	while (x < X)
	{
		config->rays[x] = malloc(sizeof(t_rays));
		config->walls[x] = malloc(sizeof(t_wall));
		config->rays[x]->dest = render_ray(config, x);
		config->rays[x]->ray_angle = config->ray_angle;
		config->ray_angle += 60.0 / X;
		angle = config->player->angle - config->ray_angle;
		f = config->rays[x]->dest * cos(deg_to_rad(angle));
		config->wall_h = ((float)y * 64.0) / f;
		config->walls[x]->x1 = (Y / 2) - (config->wall_h / 2);
		config->walls[x]->x2 = (Y / 2) + (config->wall_h / 2);
		x++;
	}
	draw_map(config);
	mlx_put_image_to_window(config->data_mlx->mlx, config->data_mlx->mlx_win,
		config->data_mlx->img.img, 0, 0);
}
