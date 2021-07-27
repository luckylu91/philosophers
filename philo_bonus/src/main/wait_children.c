#include "philosophers.h"

void	wait_children(t_table *table)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < table->params.n_philo)
	{
		waitpid(table->philos_pid[i], &wstatus, 0);
		// printf("exited: %s\n", WIFEXITED(wstatus) ? "true" : "false");
		// printf("signaled: %s\n", WIFSIGNALED(wstatus) ? "true" : "false");
		// if (WIFSIGNALED(wstatus))
		// 	printf("Term signal = %d\n", WTERMSIG(wstatus));
		// printf("pourtant pid = %d\n", table->philos_pid[i]);
	}
}
