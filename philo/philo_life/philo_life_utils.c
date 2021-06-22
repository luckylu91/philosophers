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

void	take_fork(t_philo *p, int left)
{
	if (p->stop_when_possible)
		return ;
	if (left)
		pthread_mutex_lock(p->left);
	else
		pthread_mutex_lock(p->right);
	say(p, "has taken a fork");
}

void	putback_fork(t_philo *p, int left)
{
	if (left)
		pthread_mutex_unlock(p->left);
	else
		pthread_mutex_unlock(p->right);
}
