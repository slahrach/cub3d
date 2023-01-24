/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 06:52:58 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/24 06:41:23 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_if_texture(t_config *config, char **info)
{
	int			i;
	char		**expec_textures;
	t_texture	*new;

	expec_textures = ft_split("NO SO EA WE", ' ');
	i = 0;
	while (expec_textures[i])
	{
		if (!ft_strcmp(expec_textures[i], info[0]))
		{
			if (ft_check_existing_element(info[0], config->textures))
				ft_handle_error("element already exist");
			if (open(info[1], O_RDONLY) < 0)
				ft_handle_error("cant open texture file");
			new = ft_texturenew(info[0], info[1]);
			ft_addtexture_back(&(config->textures), new);
			ft_free_matrix(expec_textures);
			ft_free_matrix(info);
			return (1);
		}
		i++;
	}
	ft_free_matrix(expec_textures);
	return (0);
}

static void	fill(char *name, char *color, t_config *config)
{
	if (!ft_strcmp(name, "F"))
	{
		if (config->f_color)
			ft_handle_error("f element already exist");
		config->f_color = color;
	}
	else
	{
		if (config->c_color)
			ft_handle_error("c element already exist");
		config->c_color = color;
	}
}

static int	check_if_colors(t_config *config, char **info)
{
	char	*color;
	char	**rgb;
	int		k;

	k = 1;
	color = NULL;
	if (!ft_strcmp(info[0], "C") || !ft_strcmp(info[0], "F"))
	{
		while (k < ft_get_matrix_size(info))
		{
			color = ft_strjoin1(color, info[k]);
			k++;
		}
		rgb = ft_split(color, ',');
		if (!ft_is_color(rgb))
			ft_handle_error("Not a valid color");
		fill(info[0], color, config);
		ft_free_matrix(info);
		ft_free_matrix(rgb);
		return (1);
	}
	return (0);
}

void	ft_check_elements(t_config *config, char *element)
{
	char		**info;

	info = ft_split(element, ' ');
	if (!ft_strchr(element, ',') && ft_get_matrix_size(info) != 2)
		ft_handle_error("more or less info");
	if ((ft_strchr(element, ',') && count_char(element, ',') != 2))
		ft_handle_error("extra or missing comma");
	if (check_if_texture(config, info))
		return ;
	if (check_if_colors(config, info))
		return ;
	ft_free_matrix(info);
	ft_handle_error("Not a valid element");
}
