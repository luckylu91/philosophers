#include "philosophers.h"

//
void print_pids(t_table *t)
{
	int i = -1;

	while (++i < t->params.n_philo)
	{
		printf("%d\n", t->philos_pid[i]);
	}
	printf("watcher : %d\n", t->death_watcher_pid);
}

int main(int argc, char **argv)
{
	t_table	table;
	int		wstatus;

	//
	setbuf(stdout, NULL);
	//
	if (create_table(argc, argv, &table))
		return (quit_main(&table));
	if (table.params.n_times_eat == 0)
	{
		printf("All philosophers ate 0 time each. What a shame...");
		return (quit_main(&table));
	}
	if (launch_simulation(&table))
	{
		printf("Oh\n");
		return (kill_and_quit(&table));
	}
	// sem_wait(table.death);
	if (sem_wait(table.death))
	{
		printf("Ah\n");
		perror(NULL);
		return (kill_and_quit(&table));
	}
	printf("lol_main\n");
	waitpid(table.death_watcher_pid, &wstatus, WNOHANG);
	if (WIFEXITED(wstatus))
	{
		tell_end(&table);
		printf("A");
	}
	else
		printf("B");
	kill_and_quit(&table);
}
