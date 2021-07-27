#include "philosophers.h"

void *philo_death_watching(void *philo_ptr)
{
	t_philo			*p;
	struct timeval	tv;

	p = (t_philo*)philo_ptr;
	while (1)
	{
		usleep(10);
		gettimeofday(&tv, NULL);
		if (delta_time(get_last_eat(p) ,tv) >= p->params->t_die)
		{
			sem_wait(p->speak_right);
			printf("%ld %d has died\n", tick(p), p->i_philo);
			sem_post(p->death);
			sem_post(p->speak_right);
			exit(PHILO_DEATH);
		}
	}
	return NULL;
}

void philo_life(t_table *table, int i)
{
	t_philo		philo;
	pthread_t	son;

	init_philo(table, i, &philo);
	sem_wait(table->simulation_can_start);
	gettimeofday(&philo.last_eat, NULL);
	pthread_create(&son, NULL, philo_death_watching, &philo);
	while (1)
	{
		say(&philo, "is thinking");
		take_forks(&philo);
		gettimeofday(&philo.action_begining, NULL);
		philo_eat(&philo);
		gettimeofday(&philo.action_begining, NULL);
		putback_forks(&philo);
		if (philo.params->n_times_eat > 0 && ++philo.n_times_eaten >= philo.params->n_times_eat)
			exit(0);
		philo_sleep(&philo);
	}
}
