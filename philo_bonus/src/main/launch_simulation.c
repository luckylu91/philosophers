#include "philosophers.h"

int	launch_simulation(t_table *table)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < table->params.n_philo)
	{
		pid = fork();
		if (pid == 0)
			philo_life(table, i);
		else if (pid > 0)
			table->philos_pid[i] = pid;
		else
			return (1);
	}
	i = -1;
	while (++i < table->params.n_philo)
		sem_post(table->simulation_can_start);
	return (0);
}
