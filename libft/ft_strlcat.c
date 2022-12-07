/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:54:55 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/12 22:06:49 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!src)
		return (dstsize);
	src_len = ft_strlen(src);
	if (!dst || dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	i = -1;
	while (src[++i] && dst_len + i < dstsize - 1)
		dst[dst_len + i] = src[i];
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
