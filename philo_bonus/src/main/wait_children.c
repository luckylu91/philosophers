#include "philosophers.h"

void	wait_children(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->params.n_philo)
		waitpid(table->philos_pid[i], NULL, 0);
}
