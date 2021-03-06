#include "philosophers.h"

void	quit(t_table *table)
{
	int	i;

	if (table->philos && table->forks)
	{
		i = -1;
		while (++i < table->params.n_philo)
			pthread_mutex_destroy(&table->forks[i]);
	}
	free(table->philos);
	free(table->forks);
	free(table);
}

int	error_quit(t_table *table)
{
	quit(table);
	return (-1);
}
