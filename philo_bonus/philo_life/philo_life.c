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
}


void philo_life(t_table *table, int i)
{
	t_philo	philo;

	init_philo(table, i, &philo);
	sem_wait(table->simulation_can_start);
	sem_post(table->simulation_can_start);
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
		{
			printf("lol_philo %d\n", philo.i_philo);
			exit(0);
		}
		putback_forks(&philo);
		philo_sleep(&philo);
	}
}
