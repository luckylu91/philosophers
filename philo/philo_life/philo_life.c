#include "philosophers.h"

static void	philo_eat(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	pthread_mutex_lock(&p->last_eat_lock);
	gettimeofday(&p->last_eat, NULL);
	pthread_mutex_unlock(&p->last_eat_lock);
	say(p, "is eating");
	corrected_sleep(p->params->t_eat, p->action_begining);
}

static void	philo_sleep(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is sleeping");
	corrected_sleep(p->params->t_sleep, p->action_begining);
}

void	*philo_life(t_philo *p)
{
	int	n_times_eat;

	n_times_eat = 0;
	gettimeofday(&p->last_eat, NULL);
	p->is_init = 1;
	while (!p->stop_when_possible)
	{
		say(p, "is thinking");
		take_fork(p, 1);
		take_fork(p, 0);
		gettimeofday(&p->action_begining, NULL);
		philo_eat(p);
		gettimeofday(&p->action_begining, NULL);
		p->n_times_eaten++;
		putback_fork(p, 0);
		putback_fork(p, 1);
		philo_sleep(p);
	}
	return (NULL);
}
