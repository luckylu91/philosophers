#include "philosophers.h"

int	quit_main(t_table *t)
{
	sem_unlink("/start");
	sem_unlink("/speak");
	sem_unlink("/eat");
	sem_unlink("/forks");
	sem_unlink("/death");
	quit_others(t);
	return (1);
}

int	quit_others(t_table *t)
{
	sem_close(t->simulation_can_start);
	sem_close(t->speak_right);
	sem_close(t->eat_queue);
	sem_close(t->forks);
	sem_close(t->death);
	free(t->philos_pid);
	return (1);
}

int	kill_and_quit(t_table *t)
{
	int i;

	i = -1;
	while (++i < t->params.n_philo)
	{
		kill(t->philos_pid[i], SIGINT);
	}
	quit_main(t);
	return (1);
}
