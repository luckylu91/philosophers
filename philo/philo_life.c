#include "philosophers.h"

static void	philo_eat(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	p->is_eating = 1;
	say(p, "is eating");
	usleep(p->params->t_eat);
	p->is_eating = 0;
	tick(NULL, &p->last_eat);
}

static void	philo_sleep(t_philo *p)
{
	struct timeval	begin;
	struct timeval	tv;
	long			nap_time;

	if (p->stop_when_possible)
		return ;
	say(p, "is sleeping");
	usleep(p->params->t_sleep);
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
	init_eat(p);
	while (!p->stop_when_possible)
	// while (1)
	{
		say(p, "is thinking");
		take_fork(p, 0);
		take_fork(p, 1);
		philo_eat(p);
		p->n_times_eaten++;
		putback_fork(p, 0);
		putback_fork(p, 1);
		philo_sleep(p);
	}
	return (NULL);
}
