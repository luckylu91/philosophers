/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crate_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:51:32 by lzins             #+#    #+#             */
/*   Updated: 2021/06/14 23:46:48 by lzins            ###   ########lyon.fr   */
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

void	distrubute_forks(t_table *table)
{
	int	i;

	table->philos[0].left = &table->forks[table->params.n_philo - 1];
	table->philos[0].right = &table->forks[0];
	i = 0;
	while (++i < table->params.n_philo)
	{
		table->philos[i].left = &table->forks[i - 1];
		table->philos[i].right = &table->forks[i];
	}
}

int	create_table(int argc, char **argv, t_table **table)
{
	int	ret;

	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
		return (error_quit(*table));
	ret = 0;
	if (handle_args(argc, argv, *table))
		return (error_quit(*table));
	if (pthread_mutex_init(&(*table)->speak_right, NULL))
		return (error_quit(*table));
	if (create_philos(*table))
		return (error_quit(*table));
	if (create_forks(*table))
		return (error_quit(*table));
	distrubute_forks(*table);
	gettimeofday(&(*table)->beginning, NULL);
	return (0);
}
