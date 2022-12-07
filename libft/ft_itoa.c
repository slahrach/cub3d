/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:16:24 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/12 19:00:20 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(int n)
{
	int	r;

	r = 0;
	if (n < 0)
		r++;
	while (n)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	long	n;
	int		r;

	n = nbr;
	r = count(nbr);
	str = malloc ((r + 1) * sizeof (char));
	if (!str)
		return (NULL);
	str[r--] = '\0';
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n)
	{
		str[r--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
