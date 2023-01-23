/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:53:24 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/23 09:11:36 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_color(char **rgb)
{
	int	i;
	int	atoi;

	i = 0;
	if (ft_get_matrix_size(rgb) != 3)
		return (0);
	while (rgb[i])
	{
		if (rgb[i][0] == '+')
			atoi = ft_atoi_(rgb[i] + 1);
		else
			atoi = ft_atoi_(rgb[i]);
		if (atoi < 0 || atoi > 255)
			return (0);
		if (!atoi && ft_strcmp(rgb[i], "0"))
			return (0);
		i++;
	}
	return (1);
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_atoi_(const char *str)
{
	int		sign;
	size_t	nbr;

	sign = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' )
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (*str)
		return (0);
	return ((sign * nbr));
}

void	ft_textureclear(t_texture **lst)
{
	t_texture	*temp;

	if (!(*lst))
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->id);
		free((*lst)->path);
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}
