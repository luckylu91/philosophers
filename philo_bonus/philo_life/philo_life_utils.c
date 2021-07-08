#include "philosophers.h"

void	take_forks(t_philo *p)
{
	sem_wait(p->eat_queue);
	sem_wait(p->forks);
	say(p, "has taken a fork");
	sem_wait(p->forks);
	say(p, "has taken a fork");
	sem_post(p->eat_queue);
}

void	putback_forks(t_philo *p)
{
	sem_post(p->forks);
	sem_post(p->forks);
}

void	philo_death(t_philo *p)
{
	printf("lol_death %d\n", p->i_philo);
	sem_wait(p->speak_right);
	printf("%ld %d has died\n", tick(p), p->i_philo);
	sem_post(p->death);
	exit(0);
}
