/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crate_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:51:32 by lzins             #+#    #+#             */
/*   Updated: 2021/07/07 08:46:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_philos(t_table *table)
{
// 	int	i;

	table->philos_pid = ft_calloc(table->params.n_philo, sizeof(pid_t));
	if (!table->philos_pid)
		return (-1);
// 	i = -1;
// 	while (++i < table->params.n_philo)
// 	{
// 		table->philos[i].i_philo = i + 1;
// 		table->philos[i].params = &table->params;
// 		table->philos[i].speak_right = &table->speak_right;
// 		table->philos[i].eat_queue = &table->eat_queue;
// 		table->philos[i].begining = &table->beginning;
// 		table->philos[i].forks = &table->forks;
// 	}
	return (0);
}

int	create_table(int argc, char **argv, t_table *table)
{
	ft_bzero(table, sizeof(t_table));
	gettimeofday(&table->beginning, NULL);
	if (handle_args(argc, argv, &table->params)
		|| create_sem("/start", &table->simulation_can_start, 0)
		|| create_sem("/speak", &table->speak_right, 1)
		|| create_sem("/eat", &table->eat_queue, 1)
		|| create_sem("/forks", &table->forks, table->params.n_philo)
		|| create_sem("/death", &table->death, 0)
		|| create_philos(table))
		return (1);
	return (0);
}
