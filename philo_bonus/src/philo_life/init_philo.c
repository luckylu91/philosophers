#include "philosophers.h"

void	init_philo(t_table *table, int i, t_philo *p)
{
	ft_bzero(p, sizeof(t_philo));
	p->i_philo = i + 1;
	p->params = &table->params;
	p->begining = &table->beginning;
	p->speak_right = table->speak_right;
	p->eat_queue = table->eat_queue;
	p->forks = table->forks;
	p->death = table->death;
	p->last_eat_access = table->last_eat_access_array[i];
}
