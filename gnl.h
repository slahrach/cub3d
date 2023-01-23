/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <kessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:22:18 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/23 02:36:23 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
size_t		ft_strlen1(char *s);
char		*ft_strnchr(char *s, int c, int *i);
char		*ft_strjoin1(char *s1, char *s2);
char		*ft_strdup1(char *s1);
size_t		ft_strlcpy1(char *dst, char *src, size_t sizedst);
char		*gnl(int fd);
#endif