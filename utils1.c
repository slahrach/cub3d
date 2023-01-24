/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:51:51 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 07:07:07 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_existing_element(char *id, t_texture *list)
{
	while (list)
	{
		if (!ft_strcmp(id, list->id))
			return (1);
		list = list->next;
	}
	return (0);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_get_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

unsigned int	rgb_to_hex(char	*color)
{
	unsigned int	hex;
	char			**rgb;

	rgb = ft_split(color, ',');
	hex = atoi(rgb[0]) << 16 | atoi(rgb[1]) << 8 | atoi(rgb[2]);
	ft_free_matrix(rgb);
	return (hex);
}

void	ft_strmapi_(char const *s,
	void (*f)(char, t_config *), t_config *config)
{
	unsigned int	i;
	size_t			l;

	if (!s)
		return ;
	l = ft_strlen(s);
	if (l < 1)
		return ;
	ft_check_1(s[0], config);
	ft_check_1(s[l - 1], config);
	i = 0;
	while (s[i])
	{
		f(s[i], config);
		i++;
	}
}
