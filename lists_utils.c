/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:46:53 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/23 09:11:27 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_addtexture_back(t_texture **head, t_texture *new)
{
	t_texture	*last;

	if (new != NULL)
	{
		if (ft_texturesize(*(head)) > 0)
		{
			last = ft_texturelast(*(head));
			last->next = new;
		}
		else
			ft_addtexture_front(head, new);
	}
}

void	ft_addtexture_front(t_texture **head, t_texture *new)
{
	new->next = *(head);
	*(head) = new;
}

t_texture	*ft_texturelast(t_texture *lst)
{
	if (ft_texturesize(lst) == 0)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_texture	*ft_texturenew(char *id, char *path)
{
	t_texture	*lst;

	lst = (t_texture *)malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->id = ft_strdup(id);
	lst->path = ft_strdup(path);
	lst->next = NULL;
	return (lst);
}

int	ft_texturesize(t_texture *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}
