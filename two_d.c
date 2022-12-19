/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:45:25 by slahrach          #+#    #+#             */
/*   Updated: 2022/12/16 21:12:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	draw_square(t_data *data, int x, int y, int color, int l)
{
	int	x1;
	int	y1;

	y1 = y;
	while(y1 < y + l)
	{
		x1 = x;
		while(x1 < x + l)
		{
			my_mlx_pixel_put(data, x1, y1, color);
			x1++;
		}
		y1++;
	}
}

void	draw_line (t_data *data, int x0,int y0,int x1,int y1)
{
	int dy, dx, incrE, incrNE, d,x,y;

	dx = x1 - x0;
	dy = y1 - y0;
	d = 2 * dy - dx;
	incrE = 2*dy;
	incrNE = 2*(dy - dx);
	x = x0;
	y = y0;

	if (x0 == x1)
	{
		if (y0 < y1)
		{
			y = y0;
			dy = y1;
		}
		else
		{
			y = y1;
			dy = y0;
		}
		while (y < dy)
		{
			my_mlx_pixel_put(data, x0, y, 0x00FF0000);
			y++;
		}
		return ;
	}
	if (y0 == y1)
	{
		if (x0 < x1)
		{
			x = x0;
			dx = x1;
		}
		else
		{
			x = x1;
			dx = x0;
		}
		while (x < dx)
		{
			my_mlx_pixel_put(data, x, y0, 0x00FF0000);
			x++;
		}
		return ;
	}
  	my_mlx_pixel_put(data, x, y, 0x00FF0000);
  	while(x < x1)
    {
      	if (d <= 0)
		{
			d += incrE;
			x++;
		}
      	else
		{
			d += incrNE;
			x++;
			y++;
		}
      	my_mlx_pixel_put(data, x, y, 0x00FF0000);
    } 
}
void	init_window(t_config *config)
{
	config->data_mlx->mlx = mlx_init();
	config->data_mlx->mlx_win = mlx_new_window(config->data_mlx->mlx, config->map_width * 48, config->map_len * 48, "Hello world!");
}

void	draw_minimap(t_config *config)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	config->data_mlx->img = mlx_new_image(config->data_mlx->mlx, config->map_width * 16, config->map_len * 16);
	config->data_mlx->addr = mlx_get_data_addr(config->data_mlx->img, &config->data_mlx->bits_per_pixel, &config->data_mlx->line_length,
		&config->data_mlx->endian);
	map = config->map;
	while(j < config->map_len)
	{
		i = 0;
		while (i < ft_strlen(map[j]))
		{
			if (map[j][i] == '1')
				draw_square(config->data_mlx, i * 16, j * 16, 0x00FFFFFF, 16);
			else if (map[j][i] != ' ')
				draw_square(config->data_mlx, i * 16, j * 16, 0x00000000, 16);
			i++;
		}
		j++;
	}
	draw_square(config->data_mlx, config->px * 16 + 4, config->py * 16 + 4, 0x00FF0000, 8);
	draw_line(config->data_mlx, config->px * 16 + 6, config->py * 16 + 6, config->px * 16 + 6 + cos(config->r) * 20, config->py * 16 + 6 + sin(config->r) * 20);
	mlx_put_image_to_window(config->data_mlx->mlx, config->data_mlx->mlx_win, config->data_mlx->img, 0, 0);
}

int	free_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->mlx);
	exit (0);
	return (0);
}

int	key_hook(int keycode, t_config *config)
{
	int	x;
	int	y;

	if(keycode == 53)
		free_exit(config->data_mlx );
	printf("%d\n", keycode);
	x = config->px;
	y = config->py;
	if (keycode == 123)
		config->r--;
	if (keycode == 124)
		config->r++;
	if (keycode == 2)
        x+=1;
    else if (keycode == 0)
        x-=1;
    else if (keycode == 13)
        y-=1;
    else if (keycode == 1)
        y+=1;
	if (config->map[y][x] != '1')
	{
		config->px = x;
		config->py = y;
	}
	mlx_destroy_image(config->data_mlx->mlx, config->data_mlx->img);
	draw_minimap(config);
	return (keycode);
}


void	ft_raycast(t_config *config)
{
	init_window(config);
	draw_minimap(config);
	mlx_hook(config->data_mlx->mlx_win, 17, 0L, free_exit, config->data_mlx);
	mlx_key_hook(config->data_mlx->mlx_win, key_hook, config);
	mlx_loop(config->data_mlx->mlx);
}