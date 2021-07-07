/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_numeric_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 23:58:37 by lzins             #+#    #+#             */
/*   Updated: 2021/06/22 16:23:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static int	ft_all_in(char *str, char *set)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(set, str[i]))
			return (0);
	}
	return (1);
}

int	invalid_numeric_arg(char *arg)
{
	return (!arg || !*arg || !ft_all_in(arg, "0123456789"));
}
