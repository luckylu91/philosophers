#include "philosophers.h"

void	init_philo(t_table *table, int i, t_philo *p)
{
	ft_bzero(p, sizeof(t_philo));
	p->i_philo = i + 1;
	p->params = &table->params;
	p->begining = &table->beginning;
	p->speak_right = table->speak_right;
	p->eat_queue = table->eat_queue;
	p->forks = table->forks;
	p->death = table->death;
}

void	take_forks(t_philo *p)
{
	sem_wait(p->eat_queue);
	sem_wait(p->forks);
	sem_wait(p->forks);
	sem_post(p->eat_queue);
}

void	putback_forks(t_philo *p)
{
	sem_post(p->forks);
	sem_post(p->forks);
}

void	philo_death(t_philo *p)
{
	sem_wait(p->speak_right);
	printf("%ld %d has died\n", tick(p), p->i_philo);
	sem_post(p->death);
	exit(0);
}
