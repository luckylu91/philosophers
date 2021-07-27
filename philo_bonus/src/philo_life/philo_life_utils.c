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

struct timeval	get_last_eat(t_philo *p)
{
	struct timeval	ret;

	sem_wait(p->last_eat_access);
	ret = p->last_eat;
	sem_post(p->last_eat_access);
	return (ret);
}

void	set_last_eat(t_philo *p, struct timeval *time_eat)
{
	sem_wait(p->last_eat_access);
	p->last_eat = *time_eat;
	sem_post(p->last_eat_access);
}
