#include "philosophers.h"

void	tell_death(t_table *table, t_philo *p)
{
	pthread_mutex_lock(&table->speak_right);
	printf("%ld %d has died\n", tick(p), p->i_philo);
	struct timeval tv;
	gettimeofday(&tv, NULL);
}

void	tell_end(t_table *table)
{
	pthread_mutex_lock(&table->speak_right);
	printf("All philosophers have eaten %d times\n", table->params.n_times_eat);
}
