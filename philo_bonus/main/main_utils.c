#include "philosophers.h"

void	watch_death(t_table *table)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < table->params.n_philo)
	{
		waitpid(table->philos_pid[i], &wstatus, 0);
	}
	sem_post(table->death);
	exit(0);
}

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
	pid = fork();
	if (pid == 0)
	{
		watch_death(table);
	}
	else if (pid > 0)
	{
		table->death_watcher_pid = pid;
	}
	else
		return (1);
	return (0);
}
