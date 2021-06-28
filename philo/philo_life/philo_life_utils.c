#include "philosophers.h"

void	say(t_philo *p, char *message)
{
	pthread_mutex_lock(p->speak_right);
	if (p->stop_when_possible)
	{
		pthread_mutex_unlock(p->speak_right);
		return ;
	}
	printf("%ld %d %s\n", tick(p), p->i_philo, message);
	pthread_mutex_unlock(p->speak_right);
}

// void	take_forks(t_philo *p)
// {
// 	int	i1;
// 	int	i2;

// 	if (p->stop_when_possible)
// 		return ;
// 	i1 = p->i_philo - 1;
// 	i2 = p->i_philo % p->params->n_philo;
// 	pthread_mutex_lock(p->eat_right);
// 	while ((*p->forks)[i1] != 0 || (*p->forks)[i2] != 0 || !p->can_take_forks)
// 	{
// 		if ((*p->forks)[i1] == 1 && (*p->forks)[i2] == 0)
// 			p->can_take_forks = 1;
// 		pthread_mutex_unlock(p->eat_right);
// 		pthread_mutex_lock(p->eat_right);
// 	}
// 	p->can_take_forks = 0;
// 	(*p->forks)[i1] = 1;
// 	(*p->forks)[i2] = 1;
// 	pthread_mutex_unlock(p->eat_right);
// 	say(p, "has taken a fork");
// 	say(p, "has taken a fork");
// }

void	take_fork(t_philo *p, int left);
void	putback_fork(t_philo *p, int left);

// void	putback_forks(t_philo *p)
// {
// 	int	i1;
// 	int	i2;
	
// 	i1 = p->i_philo - 1;
// 	i2 = p->i_philo % p->params->n_philo;
// 	pthread_mutex_lock(p->eat_right);
// 	(*p->forks)[i1] = 0;
// 	(*p->forks)[i2] = 0;
// 	pthread_mutex_unlock(p->eat_right);
// }
