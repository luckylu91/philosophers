/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crate_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:51:32 by lzins             #+#    #+#             */
/*   Updated: 2021/07/30 15:33:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_philos(t_table *table)
{
	int		i;
	char	sem_name[100];
	char	*sem_name_end;

	table->philos_pid = ft_calloc(table->params.n_philo, sizeof(pid_t));
	if (!table->philos_pid)
		return (-1);
	table->last_eat_access_array = \
		ft_calloc(table->params.n_philo, sizeof(sem_t *));
	if (!table->last_eat_access_array)
		return (-1);
	sem_name_end = ft_stpcpy(sem_name, "/philo_last_eat_access_");
	i = -1;
	while (++i < table->params.n_philo)
	{
		ft_stricpy(sem_name_end, i);
		create_sem(sem_name, &table->last_eat_access_array[i], 1);
	}
	return (0);
}

int	create_table(int argc, char **argv, t_table *table)
{
	ft_bzero(table, sizeof(t_table));
	gettimeofday(&table->beginning, NULL);
	if (handle_args(argc, argv, &table->params)
		|| create_sem("/philo_start", &table->simulation_can_start, 0)
		|| create_sem("/philo_speak", &table->speak_right, 1)
		|| create_sem("/philo_eat", &table->eat_queue, 1)
		|| create_sem("/philo_forks", &table->forks, table->params.n_philo)
		|| create_sem("/philo_death", &table->death, 0)
		|| create_philos(table))
		return (1);
	return (0);
}
