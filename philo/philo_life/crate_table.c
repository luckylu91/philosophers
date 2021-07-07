/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crate_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:51:32 by lzins             #+#    #+#             */
/*   Updated: 2021/06/23 15:20:35 by lzins            ###   ########lyon.fr   */
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
		table->philos[i].forks = &table->forks;
		table->philos[i].eat_right = &table->eat_right;
		//
		table->philos[i].can_take_forks = 1;
	}
	return (0);
}

int	create_forks(t_table *table)
{
	table->forks = ft_calloc(table->params.n_philo, sizeof(int));
	if (!table->forks)
		return (-1);
	return (0);
}

int	create_table(int argc, char **argv, t_table **table)
{
	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
		return (1);
	gettimeofday(&(*table)->beginning, NULL);
	if (handle_args(argc, argv, *table)
		|| pthread_mutex_init(&(*table)->speak_right, NULL)
		|| pthread_mutex_init(&(*table)->eat_right, NULL)
		|| create_philos(*table)
		|| create_forks(*table))
		return (1);
	return (0);
}
