/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:42:48 by lzins             #+#    #+#             */
/*   Updated: 2021/06/28 17:18:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	delta_time(struct timeval tv1, struct timeval tv2)
{
	return ((tv2.tv_sec - tv1.tv_sec) * 1000
		+ (tv2.tv_usec - tv1.tv_usec) / 1000);
}

long	tick(t_philo *p)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (delta_time(*(p->begining), tv));
}

long	tick_table(t_table *table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (delta_time(table->beginning, tv));
}

void	corrected_sleep(int duration, struct timeval begining)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	while (delta_time(begining, tv) < duration)
	{
		usleep(10);
		gettimeofday(&tv, NULL);
	}
}
