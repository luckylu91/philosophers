/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crate_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:51:32 by lzins             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/22 16:45:28 by lzins            ###   ########lyon.fr   */
=======
/*   Updated: 2021/07/07 06:57:11 by lzins            ###   ########lyon.fr   */
>>>>>>> 5d1361943f753bc88143c365d0ea5b601adf91c9
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philos(t_table *table)
{
	int	i;

	table->philos = ft_calloc(table->params.n_philo, sizeof(t_philo));
	if (!table->philos)
		return (-1);
	i = -1;
	while (++i < table->params.n_philo)
	{
		table->philos[i].params = &table->params;
		table->philos[i].speak_right = &table->speak_right;
		table->philos[i].i_philo = i + 1;
		table->philos[i].begining = &table->beginning;
<<<<<<< HEAD
=======
		table->philos[i].forks = &table->forks;
		// table->philos[i].eat_right = &table->eat_right;
		//
		table->philos[i].can_take_forks = 1;
>>>>>>> 5d1361943f753bc88143c365d0ea5b601adf91c9
	}
	return (0);
}

int	create_forks(t_table *table)
{
	int	i;
	int	ret;

	table->forks = ft_calloc(table->params.n_philo, sizeof(t_fork));
	if (!table->forks)
		return (-1);
	ret = 0;
	i = -1;
	while (++i < table->params.n_philo && !ret)
	{
		if (pthread_mutex_init(table->forks + i, NULL))
			ret = -1;
	}
	return (ret);
}

void	distribute_forks(t_table *table)
{
	int	i;
	int	n;

	n = table->params.n_philo;
	i = -1;
	while (++i < table->params.n_philo)
	{
		table->philos[i].left = &table->forks[(i - 1) % n];
		table->philos[i].right = &table->forks[i];
	}
}

int	create_table(int argc, char **argv, t_table **table)
{
	int	ret;

	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
		return (1);
	gettimeofday(&(*table)->beginning, NULL);
	if (handle_args(argc, argv, &(*table)->params)
		|| pthread_mutex_init(&(*table)->speak_right, NULL)
		// || pthread_mutex_init(&(*table)->eat_right, NULL)
		|| create_philos(*table)
		|| create_forks(*table))
		return (1);
	distribute_forks(*table);
	gettimeofday(&(*table)->beginning, NULL);
	return (0);
}
