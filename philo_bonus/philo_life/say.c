#include "philosophers.h"

void	say(t_philo *p, char *message)
{
	sem_wait(p->speak_right);
	printf("%ld %d %s\n", tick(p), p->i_philo, message);
	sem_post(p->speak_right);
}

void	tell_end(t_table *table)
{
	sem_wait(table->speak_right);
	printf("All philosophers have eaten %d times\n", table->params.n_times_eat);
}
