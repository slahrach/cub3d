/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:46:16 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/12 19:21:27 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *origin, const char *find, size_t len)
{
	size_t	l;
	size_t	i;
	size_t	a;

	i = 0;
	if (!find || find[0] == '\0')
		return ((char *)origin);
	l = ft_strlen(find);
	a = len;
	while (origin[i] && len-- && i + l <= a)
	{
		if (ft_memcmp (origin + i, find, l) == 0)
			return ((char *)origin + i);
		i++;
	}
	return (0);
}

#include <stdio.h>
#include <string.h>
int main()
{
	char s1[] = "y";
	char s2[] = "";
	//size_t max = strlen(s2);
	printf("%s\n",strnstr(s1, s2, 0));
	printf("%s",ft_strnstr(s1, s2, 0));
}
