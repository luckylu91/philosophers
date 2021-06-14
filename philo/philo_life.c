#include "philosophers.h"

static void	philo_eat(t_param *p)
{
	// if (p->stop_when_possible)
	// 	return ;
	p->is_eating = 1;
	say(p, "is eating", 0);
	usleep(p->t_eat);
	p->is_eating = 0;
	tick(p, &p->last_eat);
}

static void	philo_sleep(t_param *p)
{
	// if (p->stop_when_possible)
	// 	return ;
	say(p, "is sleeping", 0);
	usleep(p->t_sleep);
}

void	*philo_life(t_param *p)
{
	int	n_times_eat;

	// printf("Hello life, here %d inside thread %lu\n", p->i_philo, p->id);
	n_times_eat = 0;
	init_eat(p);
	// while (!p->stop_when_possible)
	while (1)
	{
		say(p, "is thinking", 0);
		take_fork(p, 0);
		take_fork(p, 1);
		philo_eat(p);
		putback_fork(p, 0);
		putback_fork(p, 1);
		philo_sleep(p);
	}
	return (NULL);
}
