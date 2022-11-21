/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:22:18 by slahrach          #+#    #+#             */
/*   Updated: 2022/11/21 11:34:38 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

size_t		ft_strlen1(char *s);
char		*ft_strnchr(char *s, int c, int *i);
char		*ft_strjoin1(char *s1, char *s2);
char		*ft_strdup1(char *s1);
size_t		ft_strlcpy1(char *dst, char *src, size_t sizedst);
char		*gnl(int fd);
#endif