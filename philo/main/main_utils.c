#include "philosophers.h"

int	launch_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->params.n_philo)
	{
		usleep(100);
		if (pthread_create(&table->philos[i].id, NULL,
				(void *(*)(void *))philo_life, &table->philos[i]))
			return (1);
	}
	return (0);
}

int	has_died(t_philo *p)
{
	int				ret;
	struct timeval	tv;

	if (!p->is_init)
		return (0);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&p->last_eat_lock);
	ret = delta_time(p->last_eat, tv) >= p->params->t_die;
	pthread_mutex_unlock(&p->last_eat_lock);
	return (ret);
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
