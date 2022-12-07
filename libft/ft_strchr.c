/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:36:22 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/12 22:21:06 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	l;
	size_t	i;

	i = -1;
	l = ft_strlen(s);
	while (++i <= l)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	}
	return (NULL);
}
