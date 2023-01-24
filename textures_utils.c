/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:56:12 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 06:38:11 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*find_path(char *orient, t_texture *textures)
{
	while (textures)
	{
		if (!ft_strcmp(textures->id, orient))
			return (ft_strdup(textures->path));
		textures = textures->next;
	}
	return (NULL);
}

unsigned int	get_pixel(t_img *image, int x, int y)
{
	char	*dst;

	dst = image->addr + (y * image->line_length
			+ x * (image->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

int	ft_ray_orientation(t_rays *ray)
{
	if ((int)ray->x % SIZE == 0 || (int)ray->x % SIZE == SIZE - 1)
	{
		if (ray->ray_angle < 90 || ray->ray_angle > 270)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < 180)
			return (1);
		else
			return (0);
	}
}

void	init_imgs(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		config->data_mlx->imgs[i].img
			= mlx_xpm_file_to_image(config->data_mlx->mlx,
				config->tex[i], &config->data_mlx->imgs[i].width,
				&config->data_mlx->imgs[i].height);
		if (!config->data_mlx->imgs[i].img)
			ft_handle_error("image not XPM");
		config->data_mlx->imgs[i].addr
			= mlx_get_data_addr(config->data_mlx->imgs[i].img,
				&config->data_mlx->imgs[i].bits_per_pixel,
				&config->data_mlx->imgs[i].line_length,
				&config->data_mlx->imgs[i].endian);
		i++;
	}
}

void	textures_array(t_config *config)
{
	config->tex = malloc(5 * sizeof(char *));
	config->tex[N] = find_path("NO", config->textures);
	config->tex[S] = find_path("SO", config->textures);
	config->tex[E] = find_path("EA", config->textures);
	config->tex[W] = find_path("WE", config->textures);
	config->tex[4] = NULL;
	ft_textureclear(&config->textures);
}
