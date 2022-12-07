/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:49:29 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/12 22:17:35 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	l;

	if (!s1)
		return (NULL);
	l = ft_strlen(s1) + 1;
	ptr = malloc (l * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy (ptr, s1, l);
	return (ptr);
}
