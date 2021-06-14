#include "philosophers.h"

void	say(t_param *p, char *message, int keep_lock)
{
	struct timeval	tv;

	pthread_mutex_lock(&p->speak_right);
	if (p->stop_when_possible)
	{
		pthread_mutex_unlock(&p->speak_right);
		return ;
	}
	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", tick(p, NULL), p->i_philo, message);
	if (!keep_lock)
		pthread_mutex_unlock(&p->speak_right);
}

void	take_fork(t_param *p, int left)
{
	if (left)
		pthread_mutex_lock(p->left);
	else
		pthread_mutex_lock(p->right);
	say(p, "has taken a fork", 0);
}

void	putback_fork(t_param *p, int left)
{
	if (left)
		pthread_mutex_unlock(p->left);
	else
		pthread_mutex_unlock(p->right);
}
