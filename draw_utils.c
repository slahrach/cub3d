/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 06:03:23 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 06:39:51 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

