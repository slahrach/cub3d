/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:37:00 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/23 09:13:39 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*ft_strndup(char *s1, int l)
{
	char		*ptr;

	ptr = (char *) malloc ((l + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy1 (ptr, s1, l + 1);
	return (ptr);
}

static char	*ft_strchr1(char *s, int c)
{
	size_t	l;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	l = ft_strlen1(s);
	while (i <= l)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

static	char	*funct(char **store, char *buf, int fd, int *pr)
{
	int		i;
	char	*left;
	char	*line;

	while ((*pr) > 0 || ft_strchr1(*store, '\n'))
	{
		buf[(*pr)] = '\0';
		*store = ft_strjoin1(*store, buf);
		left = ft_strnchr(*store, '\n', &i);
		if (i != -1)
		{
			line = ft_strndup(*store, i);
			free(*store);
			if (left)
				*store = left;
			else
				*store = NULL;
			return (line);
		}
		*pr = read(fd, buf, 1);
	}
	return (NULL);
}

char	*gnl(int fd)
{
	char		*retur;
	static char	*store;
	char		*buf;
	int			r;
	char		*ret;

	buf = (char *) malloc ((2) * sizeof(char));
	r = read(fd, buf, 1);
	if (r > 0 || ft_strchr1(store, '\n'))
	{
		retur = funct(&store, buf, fd, &r);
		free(buf);
		if (retur)
			return (retur);
	}
	else
		free(buf);
	if (store != NULL)
	{
		ret = ft_strdup1(store);
		free(store);
		store = NULL;
		return (ret);
	}
	return (NULL);
}
