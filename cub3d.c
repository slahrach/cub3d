/* ************************************************************************** */
/*									                                        */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:45:47 by slahrach          #+#    #+#             */
/*   Updated: 2022/11/21 12:16:39 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_error(char *error)
{
	printf("Error\n%s\n", error);
	exit(1);
}

static t_config	*ft_init(void)
{
	t_config	*game;

	game = malloc(sizeof(t_config));
	game->textures = NULL;
	game->f_color = NULL;
	game->c_color = NULL;
	game->data_mlx = malloc (sizeof (t_data));
	game->player = malloc(sizeof(t_player));
	game->map_len = 0;
	game->orientation = 0;
	game->rays = malloc(sizeof(t_rays *) * X);
	game->walls = malloc(sizeof(t_wall *) * X);
	return (game);
}

int	main(int argc, char	**argv)
{
	t_config	*game;

	game = ft_init();
	ft_init_config(game, argc, argv);
	ft_init_player(game);
	ft_raycast(game);
}
