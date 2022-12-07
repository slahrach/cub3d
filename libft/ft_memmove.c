/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:22:07 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/12 22:56:23 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (dst > src)
	{
		i = (int) len;
		while (--i >= 0)
			*(char *)(dst + i) = *(char *)(src + i);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
