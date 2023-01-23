/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:45:25 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/23 09:17:10 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_window(t_config *config)
{
	void	*img;
	int		width;
	int		height;

	config->data_mlx->mlx = mlx_init();
	config->data_mlx->mlx_win = mlx_new_window(config->data_mlx->mlx, X, Y, "Hello world!");
	config->data_mlx->img.img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->img.addr = mlx_get_data_addr(config->data_mlx->img.img, &config->data_mlx->img.bits_per_pixel, &config->data_mlx->img.line_length,&config->data_mlx->img.endian);
	init_imgs(config);
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

void	draw_player(t_config *config)
{
	config->player->j = config->player->j + config->player->y * 4.0;
	config->player->i = config->player->i + config->player->x * 4.0;
}

void	draw_minimap(t_config *config)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 28;
	while (config->map[j])
	{
		i = 0;
		x = 28;
		while (config->map[j][i])
		{
			draw_square(i, j, 28, config);
			i++;
			x = x + 28;
		}
		j++;
	}
}

double	deg_to_rad(double x)
{
	return (x / 180 * M_PI);
}

int	ft_check_wall_ray2(t_config *config, float xstart, float ystart)
{
	float	x;
	float	y;

	y = sin(deg_to_rad(config->ray_angle));
	x = cos(deg_to_rad(config->ray_angle));
	if (config->map[(int)(ystart + y) / 28][(int)(xstart) / 28] == '1' && config->map[(int)(ystart) / 28][(int)(xstart + x) / 28] == '1')
		return (1);
	else if (config->map[(int)(ystart - y) / 28][(int)(xstart) / 28] == '1' && config->map[(int)(ystart) / 28 ][(int)(xstart - x) / 28] == '1')
		return (1);
	else if (config->map[(int)(ystart + y) / 28][(int)(xstart) / 28] == '1' && config->map[(int)(ystart) / 28][(int)(xstart - x) / 28] == '1')
		return (1);
	else if (config->map[(int)(ystart - y) / 28][(int)(xstart) / 28] == '1' && config->map[(int)(ystart) / 28][(int)(xstart + x) / 28] == '1')
		return (1);
	else
		return (0);
}

int	ft_check_wall_ray(t_config *config, float xstart, float ystart)
{	
	if (config->map[(int)ystart / 28][(int)xstart / 28] == '1')
		return (0);
	return (1);
}

float	render_ray(t_config *config, int x)
{
	float	xstart;
	float	xstart_p;
	float	ystart;
	float	ystart_p;
	int		i;

	xstart = config->player->i + cos(deg_to_rad(config->player->angle));
	xstart_p = config->player->i + cos(deg_to_rad(config->player->angle));
	ystart = config->player->j + sin(deg_to_rad(config->player->angle));
	ystart_p = config->player->j + sin(deg_to_rad(config->player->angle));
	i = 0;
	while (ft_check_wall_ray(config, xstart, ystart))
	{
		ystart += sin(deg_to_rad(config->ray_angle)) / 16;
		xstart += cos(deg_to_rad(config->ray_angle)) / 16;
		i++;
	}
	config->rays[x]->x = xstart;
	config->rays[x]->y = ystart;
	return (sqrt(((xstart - xstart_p) * (xstart - xstart_p)) + ((ystart - ystart_p) * (ystart - ystart_p))));
}

int	ft_check_wall(t_config *config, int deg, int s)
{
	float	i;
	float	j;
	int		x;

	i = config->player->i;
	j = config->player->j;
	x = 0;
	while (x < 10)
	{
		if (config->map[(int)j / 28][(int)i / 28] == '1')
			return (0);
		i += cos(deg_to_rad(config->player->angle + deg)) * s;
		j += sin(deg_to_rad(config->player->angle + deg)) * s;
		x++;
	}
	return (1);
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

void	check_angle(t_config *config)
{
	if (config->player->angle > 360)
		config->player->angle -= 360;
	else if (config->player->angle < 0)
		config->player->angle += 360;
}

void	draw_game(t_config *config)
{
	int	x = 0;
	int	y;
	y = config->map_len * 28;
	config->ray_angle = config->player->angle - 30;
	while (x < X)
	{
		config->rays[x] = malloc(sizeof(t_rays));
		config->walls[x] = malloc(sizeof(t_wall));
		config->rays[x]->dest = render_ray(config, x);
		config->rays[x]->ray_angle = config->ray_angle;
		config->ray_angle += 60.0 / X;
		config->wall_h = ((float)y * 64.0) / (config->rays[x]->dest * cos(deg_to_rad(config->player->angle - config->ray_angle)));
		config->walls[x]->x1 = (Y / 2) - (config->wall_h / 2);
		config->walls[x]->x2 = (Y / 2) + (config->wall_h / 2);
		x++;
	}
	draw_map(config);
	mlx_put_image_to_window(config->data_mlx->mlx, config->data_mlx->mlx_win, config->data_mlx->img.img, 0, 0);
}

int	key_hook(int keycode, t_config *config)
{
	config->player->x = 0;
	config->player->y = 0;
	if (keycode == 2) // D
	{
		if (ft_check_wall(config, 90, 1) == 0)
			return (keycode);
		config->player->x = cos(deg_to_rad(config->player->angle + 90));
		config->player->y = sin(deg_to_rad(config->player->angle + 90));
	}
	else if (keycode == 0) // A
	{
		if (ft_check_wall(config, 90, -1) == 0)
			return (keycode);
		config->player->x = cos(deg_to_rad(config->player->angle + 90)) * -1;
		config->player->y = sin(deg_to_rad(config->player->angle + 90)) * -1;
	}
    else if (keycode == 13) //W
	{
		if (ft_check_wall(config, 0, 1) == 0)
			return (keycode);
		config->player->x = cos(deg_to_rad(config->player->angle));
		config->player->y = sin(deg_to_rad(config->player->angle));
	}
    else if (keycode == 1) // S
	{
		if (ft_check_wall(config, 0, -1) == 0)
			return (keycode);
		config->player->x = cos(deg_to_rad(config->player->angle)) * -1;
		config->player->y = sin(deg_to_rad(config->player->angle)) * -1;
	}
	else if (keycode == 124) // <-
		config->player->angle = config->player->angle + 10;
	else if (keycode == 123) // ->
		config->player->angle = config->player->angle - 10;
	else if (keycode == 53)
	{
		mlx_clear_window(config->data_mlx->mlx, config->data_mlx->mlx_win);
		exit(0);
	}
	check_angle(config);
	ft_player_angle(config->player);

	draw_player(config);

	//draw_minimap(config);
	free_rays(config);
	free_walls(config);
	draw_game(config);
	return (keycode);
}

void	draw_map(t_config *config)
{
	unsigned int		color;
	int		height;
	int		i;
	int		j;
	int		x_color;
	int		y_color;

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

int	e_hook(t_config *config)
{
	mlx_clear_window(config->data_mlx->mlx, config->data_mlx->mlx_win);
	//while (1);
	exit(0);
}

void	ft_raycast(t_config *config)
{
	init_window(config);
	draw_player(config);
	draw_game(config);
	mlx_key_hook(config->data_mlx->mlx_win, key_hook, config);
	mlx_hook(config->data_mlx->mlx_win, 17, 0, e_hook, config);
	mlx_loop(config->data_mlx->mlx);
}
