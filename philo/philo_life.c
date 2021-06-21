#include "philosophers.h"

static void	philo_eat(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is eating");
	gettimeofday(&p->last_eat, NULL);
	// usleep(1000 * p->params->t_eat);
	corrected_sleep(p->params->t_eat, p->action_begining);
}

static void	philo_sleep(t_philo *p)
{
	struct timeval	begin;
	struct timeval	tv;
	long			nap_time;

	if (p->stop_when_possible)
		return ;
	say(p, "is sleeping");
	// usleep(1000 * p->params->t_sleep);
	corrected_sleep(p->params->t_sleep, p->action_begining);

	// gettimeofday(&begin, NULL);
	// say(p, "is sleeping");
	// nap_time = p->params->t_sleep;
	// while (nap_time > 0)
	// {
	// 	if (nap_time < 10)
	// 		usleep(nap_time);
	// 	else
	// 		usleep(10);
	// 	gettimeofday(&tv, NULL);
	// 	nap_time = p->params->t_sleep - delta_time(begin, tv);
	// }
}

void	*philo_life(t_philo *p)
{
	int	n_times_eat;

	// printf("Hello life, here %d inside thread %lu\n", p->i_philo, p->id);
	n_times_eat = 0;
	gettimeofday(&p->last_eat, NULL);
	p->is_init = 1;
	while (!p->stop_when_possible)
	{
		say(p, "is thinking");
		take_fork(p, p->i_philo % 2);
		take_fork(p, p->i_philo % 2 + 1);
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
