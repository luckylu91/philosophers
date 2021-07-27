#include "philosophers.h"

void	philo_eat(t_philo *p)
{
	struct timeval	time_eat;

	if (p->stop_when_possible)
		return ;
	say(p, "is eating");
	gettimeofday(&time_eat, NULL);
	set_last_eat(p, &time_eat);
	corrected_sleep(p, p->params->t_eat);
}
