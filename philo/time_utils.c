/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:42:48 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 10:37:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	delta_time(struct timeval tv1, struct timeval tv2)
{
	return (tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000;
}

void	init_eat(t_param *p)
{
	gettimeofday(&p->last_eat, NULL);
	gettimeofday(&p->begining, NULL);
	p->is_init = 1;
}

long	tick(t_param *p, struct timeval *tparam)
{
	struct timeval	tv;
	suseconds_t		ret;

	gettimeofday(&tv, NULL);
	if (tparam)
	{
		*tparam = tv;
		return (0);
	}
	else
		return (delta_time(tv, p->begining));
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
