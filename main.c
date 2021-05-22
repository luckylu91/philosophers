/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:32:18 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 09:46:20 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	usage_error(t_param **p)
{
	ft_putstr_fd("Error: Usage: ./philosophers n_philo t_die t_eat " \
		"t_sleep [n_times_eat]\n", STDERR_FILENO);
	free(*p);
	*p = NULL;
	return (-1);
}

int	handle_args(int argc, char **argv, t_param **p)
{
	*p = NULL;
	if (argc != 5 && argc != 6)
		return (usage_error(p));
	*p = ft_calloc(1, sizeof(t_param));
	if (!*p)
		return (-1);
	(*p)->n_philo = ft_atoi(argv[1]);
	(*p)->t_die = ft_atoi(argv[2]);
	(*p)->t_eat = ft_atoi(argv[3]);
	(*p)->t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		(*p)->n_times_eat = -1;
	if (argc == 6)
		(*p)->n_times_eat = ft_atoi(argv[5]);
	if ((*p)->n_philo < 0 || (*p)->t_die < 0 || (*p)->t_eat < 0
		|| (*p)->t_sleep < 0 || (argc == 6 && (*p)->n_times_eat < 0))
		return (usage_error(p));
	return (0);
}

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
	printf("%ld %d %s\n",
		tv.tv_sec * 1000 + tv.tv_usec, p->i_philo, message);
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

void	philo_eat(t_param *p)
{
	if (p->stop_when_possible)
		return ;
	p->is_eating = 1;
	say(p, "is eating", 0);
	usleep(p->t_eat);
	p->is_eating = 0;
}

void	philo_sleep(t_param *p)
{
	if (p->stop_when_possible)
		return ;
	say(p, "is sleeping", 0);
	usleep(p->t_sleep);
}

void	*philo_life(t_param *p)
{
	int	n_times_eat;

	// printf("Hello life, here %d inside thread %lu\n", p->i_philo, p->id);
	n_times_eat = 0;
	init_eat(p);
	while (!p->stop_when_possible)
	{
		say(p, "is thinking", 0);
		take_fork(p, 0);
		take_fork(p, 1);
		philo_eat(p);
		putback_fork(p, 0);
		putback_fork(p, 1);
		philo_sleep(p);
	}
	return (NULL);
}

void quit(t_param *p, t_fork *forks)
{
	int	i;

	if (p && forks)
	{
		i = -1;
		while (++i < p[0].n_philo)
			pthread_mutex_destroy(&forks[i]);
	}
	free(p);
	free(forks);
}

int	error_quit(t_param *p, t_fork *forks)
{
	quit(p, forks);
	return (-1);
}

void print_param(t_param *p)
{
	printf("args: %d %d %d %d %d\n", p->n_philo, p->t_die, p->t_eat, p->t_sleep, p->n_times_eat);
	printf("i: %d\n", p->i_philo);
	printf("left=%p, righr=%p\n", p->left, p->right);
}

void	print_end_simulation(pthread_mutex_t *speak_right)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld End of simulation\n",
		tv.tv_sec * 1000 + tv.tv_usec);
	pthread_mutex_unlock(speak_right);
}

int	main(int argc, char **argv)
{
	t_param		*p;
	t_fork		*forks;
	int			ret;
	int			i;

	// struct timeval	tv;
	// pthread_t		thread;
	// void			*arg = NULL;
	// int				ret;
	// void			*thread_return;
	// pthread_mutex_t	mutex;
	setbuf(stdout, NULL);

	p = NULL;
	forks = NULL;
	ret = 0;
	if (handle_args(argc, argv, &p))
		return (error_quit(p, forks));
	if (pthread_mutex_init(&p->speak_right, NULL))
		return (error_quit(p, forks));
	if (duplicate_param(&p))
		return (error_quit(p, forks));
	if (create_forks(p[0].n_philo, &forks))
		return (error_quit(p, forks));
	if (!ret)
		create_table(p, forks);
	//
	i = -1;
	while (++i < p[0].n_philo)
		print_param(&p[i]);
	//
	i = -1;
	while (++i < p[0].n_philo)
	{
		if (pthread_create(&p[i].id, NULL, (void * (*)(void *))philo_life, &p[i]))
			ret = -1;
	}
	while (!ret)
	{
		i = -1;
		while (++i < p[0].n_philo)
		{
			if (has_died(&p[i]))
			{
				say(&p[i], "has died", 1);
				i = -1;
				while (++i < p[0].n_philo)
					p[i].stop_when_possible = 1;
				while (++i < p[0].n_philo)
					pthread_join(p[i].id, NULL);
				print_end_simulation(&p[0].speak_right);
				quit(p, forks);
				return (0);
			}
		}
	}
	return (0);
}
