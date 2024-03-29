/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:23:08 by kessalih          #+#    #+#             */
/*   Updated: 2023/01/24 06:44:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (config->map[(int)(ystart + y) / 64][(int)(xstart) / 64] == '1'
			&& config->map[(int)(ystart) / 64][(int)(xstart + x) / 64] == '1')
		return (1);
	else if (config->map[(int)(ystart - y) / 64][(int)(xstart) / 64] == '1'
			&& config->map[(int)(ystart) / 64][(int)(xstart - x) / 64] == '1')
		return (1);
	else if (config->map[(int)(ystart + y) / 64][(int)(xstart) / 64] == '1'
			&& config->map[(int)(ystart) / 64][(int)(xstart - x) / 64] == '1')
		return (1);
	else if (config->map[(int)(ystart - y) / 64][(int)(xstart) / 64] == '1'
			&& config->map[(int)(ystart) / 64][(int)(xstart + x) / 64] == '1')
		return (1);
	else
		return (0);
}

int	ft_check_wall_ray(t_config *config, float xstart, float ystart)
{	
	if (config->map[(int)ystart / 64][(int)xstart / 64] == '1')
		return (0);
	return (1);
}

int	ft_check_wall(t_config *config, int deg, int s)
{
	float	i;
	float	j;
	int		x;

	i = config->player->i;
	j = config->player->j;
	x = 0;
	while (x < 15)
	{
		if (config->map[(int)j / 64][(int)i / 64] == '1')
			return (0);
		i += cos(deg_to_rad(config->player->angle + deg)) * s;
		j += sin(deg_to_rad(config->player->angle + deg)) * s;
		x++;
	}
	return (1);
}

void	check_angle(t_config *config)
{
	if (config->player->angle > 360)
		config->player->angle -= 360;
	else if (config->player->angle < 0)
		config->player->angle += 360;
}
