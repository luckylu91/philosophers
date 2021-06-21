/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:32:18 by lzins             #+#    #+#             */
/*   Updated: 2021/06/21 19:43:04 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void tell_death(t_table *table, t_philo *p)
{
	pthread_mutex_lock(&table->speak_right);
	printf("%ld %d has died\n", tick(p), p->i_philo);
}
void tell_end(t_table *table)
{
	pthread_mutex_lock(&table->speak_right);
	printf("All philosophers have eaten %d times\n", table->params.n_times_eat);
}

int	test_end(t_table *table, int i)
{
	static int	n_done_eating = 0;

	if (has_died(&table->philos[i]))
	{
		tell_death(table, &table->philos[i]);
		return (1);
	}
	else if (table->params.n_times_eat >= 0)
	{
		if (table->philos[i].n_times_eaten >= table->params.n_times_eat)
			n_done_eating++;
		else
			n_done_eating = 0;
		if (n_done_eating >= table->params.n_philo)
		{
			tell_end(table);
			return (1);
		}
	}
	return (0);
}

void	end_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->params.n_philo)
		table->philos[i].stop_when_possible = 1;
	pthread_mutex_unlock(&table->speak_right);
	i = -1;
	while (++i < table->params.n_philo)
		pthread_mutex_unlock(&table->forks[i]);
	i = -1;
	printf("%ld End of simulation\n", tick_table(table));
	quit(table);
}

int	launch_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->params.n_philo)
	{
		if (pthread_create(&table->philos[i].id, NULL,
				(void * (*)(void *))philo_life, &table->philos[i]))
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;
	int		ret;

	if (create_table(argc, argv, &table)
			|| launch_simulation(table))
		return (error_quit(table));
	i = 0;
	while (1)
	{
		if (test_end(table, i))
		{
			end_simulation(table);
			return (0);
		}
		i = (i + 1) % table->params.n_philo;
	}
	return (0);
}
