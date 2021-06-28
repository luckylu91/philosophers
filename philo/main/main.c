/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:32:18 by lzins             #+#    #+#             */
/*   Updated: 2021/06/23 14:57:49 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	//
	setbuf(stdout, NULL);
	if (create_table(argc, argv, &table)
		|| launch_simulation(table))
		return (error_quit(table));
	i = 0;
	while (1)
	{
		if (test_end(table, i))
		{
			end_simulation(table);
			return (0);
		}
		i = (i + 1) % table->params.n_philo;
	}
	return (0);
}
