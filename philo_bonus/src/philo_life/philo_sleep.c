#include "philosophers.h"

void	philo_sleep(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is sleeping");
	corrected_sleep(p, p->params->t_sleep);
}
