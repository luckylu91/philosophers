#include "philosophers.h"

static void	philo_eat(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is eating");
	gettimeofday(&p->last_eat, NULL);
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
		take_forks(p);
		gettimeofday(&p->action_begining, NULL);
		philo_eat(p);
		gettimeofday(&p->action_begining, NULL);
		p->n_times_eaten++;
		putback_forks(p);
		philo_sleep(p);
	}
	return (NULL);
}
