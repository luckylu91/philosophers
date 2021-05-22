/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crate_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:51:32 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 01:51:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	duplicate_param(t_param **p)
{
	int		i;
	t_param	*p_array;

	p_array = ft_calloc((*p)->n_philo, sizeof(t_param));
	if (!p_array)
		return (-1);
	i = -1;
	while (++i < (*p)->n_philo)
		p_array[i] = **p;
	free(*p);
	*p = p_array;
	return (0);
}

int	create_forks(int n_philo, t_fork **forks_array)
{
	int	i;
	int	ret;

	*forks_array = ft_calloc(n_philo, sizeof(t_fork));
	if (!forks_array)
		return (-1);
	ret = 0;
	i = -1;
	while (++i < n_philo && !ret)
	{
		if (pthread_mutex_init((*forks_array) + i, NULL))
			ret = -1;
	}
	return (0);
}

void	create_table(t_param *p_array, t_fork *forks_array)
{
	int	i;
	int	n_philo;

	n_philo = p_array[0].n_philo;
	p_array[0].left = &forks_array[n_philo - 1];
	p_array[0].right = &forks_array[0];
	i = 0;
	while (++i < n_philo - 1)
	{
		p_array[i].left = &forks_array[i - 1];
		p_array[i].right = &forks_array[i];
	}
	i = -1;
	while(++i < n_philo)
		p_array[i].i_philo = i;
}
