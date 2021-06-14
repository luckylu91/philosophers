/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:32:18 by lzins             #+#    #+#             */
/*   Updated: 2021/06/14 12:57:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
// void print_param(t_param *p)
// {
// 	printf("args: %d %d %d %d %d\n", p->n_philo, p->t_die, p->t_eat,
// 		p->t_sleep, p->n_times_eat);
// 	printf("i: %d\n", p->i_philo);
// 	printf("left=%p, right=%p\n", p->left, p->right);
// }

void	print_end_simulation(t_param *p)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld End of simulation\n", tick(p, NULL));
	pthread_mutex_unlock(&p->speak_right);
}

int	main(int argc, char **argv)
{
	t_param		*p;
	t_fork		*forks;
	int			ret;
	int			i;

	setbuf(stdout, NULL);
	if (create_table(argc, argv, &p, &forks))
		return (1);
	//
	// i = -1;
	// while (++i < p[0].n_philo)
	// 	print_param(&p[i]);
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
				pthread_mutex_unlock(&p[0].speak_right);
				while (++i < p[0].n_philo)
					pthread_join(p[i].id, NULL);
				print_end_simulation(&p[0]);
				quit(p, forks);
				return (0);
			}
		}
	}
	return (0);
}
