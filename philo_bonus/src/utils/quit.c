#include "philosophers.h"

int	quit_main(t_table *t)
{
	int		i;
	char	sem_name[100];
	char	*sem_name_end;

	sem_unlink("/philo_start");
	sem_unlink("/philo_speak");
	sem_unlink("/philo_eat");
	sem_unlink("/philo_forks");
	sem_unlink("/philo_death");
	sem_name_end = ft_stpcpy(sem_name, "/philo_last_eat_access_");
	i = -1;
	while (++i < t->params.n_philo)
	{
		ft_stricpy(sem_name_end, i);
		sem_unlink(sem_name);
	}
	quit_others(t);
	return (1);
}

int	quit_others(t_table *t)
{
	int i;

	sem_close(t->simulation_can_start);
	sem_close(t->speak_right);
	sem_close(t->eat_queue);
	sem_close(t->forks);
	sem_close(t->death);
	i = -1;
	while (++i < t->params.n_philo)
		sem_close(t->last_eat_access_array[i]);
	free(t->last_eat_access_array);
	free(t->philos_pid);
	return (1);
}

void	kill_children(t_table *t)
{
	int i;

	i = -1;
	while (++i < t->params.n_philo)
		kill(t->philos_pid[i], SIGINT);
}

int	kill_and_quit(t_table *t)
{
	kill_children(t);
	quit_main(t);
	return (1);
}
