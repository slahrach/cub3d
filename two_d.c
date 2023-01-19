/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:45:25 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/19 06:55:25 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_window(t_config *config)
{
	config->data_mlx->mlx = mlx_init();
	config->data_mlx->mlx_win = mlx_new_window(config->data_mlx->mlx, X, Y, "Hello world!");
	config->data_mlx->img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->addr = mlx_get_data_addr(config->data_mlx->img, &config->data_mlx->bits_per_pixel, &config->data_mlx->line_length,&config->data_mlx->endian);
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
				mlx_pixel_put(config->data_mlx,config->data_mlx->mlx_win, t2, t1, 0xFFFFFF);
			else
				mlx_pixel_put(config->data_mlx,config->data_mlx->mlx_win, t2, t1, 0x000000);
			t2++;
		}
		t1++;
	}
}

void	draw_player(t_config *config)
{
	float	t1;
	float	t2;

	t1 = 0;
	while (t1 <= P_SIZE / 2)
	{
		t2 = 0;
		while (t2 <= P_SIZE / 2)
		{
			if (t1 == 0 && t2 == 0)
			{
				config->player->j = config->player->j + config->player->y * 4.0;
				config->player->i = config->player->i + config->player->x * 4.0;
			}
			//mlx_pixel_put(config->data_mlx,config->data_mlx->mlx_win ,config->player->i + t2, config->player->j + t1, 0xFF0000);
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

int	ft_check_wall_ray(t_config *config, float xstart, float ystart)
{
	int		x;
	int		i;
	int		j;

	i = xstart;
	j = ystart;
	x = 0;
	if (config->map[(int)j / 28 ][(int)i / 28 ] == '1')
			return (0);
	i += cos(deg_to_rad(config->ray_angle));
	j += sin(deg_to_rad(config->ray_angle));

	return (1);
}

float    render_ray(t_config *config)
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
		//mlx_pixel_put(config->data_mlx->mlx,config->data_mlx->mlx_win,xstart,ystart,0x00FF00);
		ystart += sin(deg_to_rad(config->ray_angle)) / 16;
		xstart += cos(deg_to_rad(config->ray_angle)) / 16;
		i++;
    }
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
	while (x < 5)
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
	else
	{
		if (keycode == 124) // <-
			config->player->angle = config->player->angle + 10;
			
		else if (keycode == 123) // ->
			config->player->angle = config->player->angle - 10;
		check_angle(config);
	}
	ft_player_angle(config->player);
	draw_map(config);
	//draw_minimap(config);
	draw_player(config);
	free_rays(config);
	free_walls(config);
	int x = 0;
	int	y;
	y = config->map_len * 28;
	config->ray_angle = config->player->angle - 30;
	while (x < X)
	{
		
		config->rays[x] = malloc(sizeof(t_rays));
		config->walls[x] = malloc(sizeof(t_wall));
		config->rays[x]->dest = render_ray(config);
		config->rays[x]->ray_angle = config->ray_angle;
		config->ray_angle += 60.0 / X;
		config->wall_h = ((float)y * 64.0) / (config->rays[x]->dest * cos(deg_to_rad(config->player->angle - config->ray_angle)));
		config->walls[x]->x1 = (Y / 2) - (config->wall_h / 2);
		config->walls[x]->x2 = (Y / 2) + (config->wall_h / 2);
		x++;
	}
	
	return (keycode);
}

void	draw_map(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	mlx_clear_window(config->data_mlx->mlx, config->data_mlx->mlx_win);
	config->data_mlx->img = mlx_new_image(config->data_mlx->mlx, X, Y);
	config->data_mlx->addr = mlx_get_data_addr(config->data_mlx->img, &config->data_mlx->bits_per_pixel, &config->data_mlx->line_length,&config->data_mlx->endian);
	while (i < X)
	{
		j = 0;
		while(j < Y)
		{
			if (j < config->walls[i]->x1)
				my_mlx_pixel_put(config->data_mlx,i,j,0x00FF00);
			//mlx_pixel_put(config->data_mlx->mlx,config->data_mlx->mlx_win,i,j,0x00FF00);
			else if (j >= config->walls[i]->x1 && j < config->walls[i]->x2)
				my_mlx_pixel_put(config->data_mlx,i,j,0xFF0000);
			//mlx_pixel_put(config->data_mlx->mlx,config->data_mlx->mlx_win,i,j,0xFF0000);
			else
				my_mlx_pixel_put(config->data_mlx,i,j,0x0000FF);
			//mlx_pixel_put(config->data_mlx->mlx,config->data_mlx->mlx_win,i,j,0x0000FF);	
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(config->data_mlx->mlx, config->data_mlx->mlx_win, config->data_mlx->img, 0, 0);
}

void	ft_raycast(t_config *config)
{
	double angle = 60;
	int		y;

	y = config->map_len * 28;
	init_window(config);
	//draw_minimap(config);
	draw_player(config);
	int x = 0;
	config->ray_angle = config->player->angle - 30;
	while (x < X)
	{
		config->rays[x] = malloc(sizeof(t_rays));
		config->walls[x] = malloc(sizeof(t_wall));
		config->rays[x]->dest = render_ray(config);
		config->rays[x]->ray_angle = config->ray_angle;
		config->ray_angle += 60.0 / X;
		config->wall_h = (float)y / config->rays[x]->dest * 64.0;
		config->walls[x]->x1 = (Y / 2.0) - (config->wall_h / 2.0);
		config->walls[x]->x2 = (Y / 2.0) + (config->wall_h / 2.0);
		x++;
	}
	draw_map(config);
	mlx_hook(config->data_mlx->mlx_win,3,0, key_hook, config);
	mlx_hook(config->data_mlx->mlx_win,2,0, key_hook, config);
	mlx_loop(config->data_mlx->mlx);
}