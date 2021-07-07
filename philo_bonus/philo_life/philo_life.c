#include "philosophers.h"

static void	philo_eat(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is eating");
	gettimeofday(&p->last_eat, NULL);
	corrected_sleep(p, p->params->t_eat);
}

static void	philo_sleep(t_philo *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is sleeping");
	corrected_sleep(p, p->params->t_sleep);
}

void philo_life(t_table *table, int i)
{
	t_philo	philo;

	init_philo(table, i, &philo);
	sem_wait(table->simulation_can_start);
	gettimeofday(&philo.last_eat, NULL);
	// while (!philo.stop_when_possible)
	while (1)
	{
		say(&philo, "is thinking");
		take_forks(&philo);
		gettimeofday(&philo.action_begining, NULL);
		philo_eat(&philo);
		gettimeofday(&philo.action_begining, NULL);
		if (philo.params->n_times_eat > 0 && ++philo.n_times_eaten >= philo.params->n_times_eat)
			exit(0);
		putback_forks(&philo);
		philo_sleep(&philo);
	}
}
