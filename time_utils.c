/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:42:48 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 09:46:33 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static suseconds_t	delta_time(struct timeval tv1, struct timeval tv2)
{
	return (tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec);
}

void	init_eat(t_param *p)
{
	gettimeofday(&p->last_eat, NULL);
	p->is_init = 1;
}

void	update_eat(t_param *p)
{
	struct timeval	tv;
	suseconds_t		ret;

	gettimeofday(&tv, NULL);
	p->last_eat = tv;
}

// int	finished_activity(t_param *p, int t_activity)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (delta_time(p->activity_begining, tv) >= t_activity);
// }

int	has_died(t_param *p)
{
	struct timeval	tv;

	if (!p->is_init || p->is_eating)
		return (0);
	gettimeofday(&tv, NULL);
	return (delta_time(p->last_eat, tv) >= p->t_die);
}
