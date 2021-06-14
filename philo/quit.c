#include "philosophers.h"

void quit(t_param *p, t_fork *forks)
{
	int	i;

	if (p && forks)
	{
		i = -1;
		while (++i < p[0].n_philo)
			pthread_mutex_destroy(&forks[i]);
	}
	free(p);
	free(forks);
}

int	error_quit(t_param *p, t_fork *forks)
{
	quit(p, forks);
	return (-1);
}
