#include "philosophers.h"

void	*waiting_death(void *table_ptr)
{
	sem_wait(((t_table *)table_ptr)->death);
	kill_children(table_ptr);
	return (NULL);
}

void	*waiting_end(void *table_ptr)
{
	wait_children(table_ptr);
	sem_post(((t_table *)table_ptr)->death);
	tell_end(table_ptr);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	watcher_death;
	pthread_t	watcher_end;

	if (create_table(argc, argv, &table))
		return (quit_main(&table));
	if (table.params.n_times_eat == 0)
	{
		printf("Each philosophers ate 0 time. What a shame...\n");
		return (quit_main(&table));
	}
	if (launch_simulation(&table))
		return (kill_and_quit(&table));
	pthread_create(&watcher_death, NULL, waiting_death, &table);
	pthread_create(&watcher_end, NULL, waiting_end, &table);
	pthread_join(watcher_death, NULL);
	pthread_join(watcher_end, NULL);
	quit_main(&table);
}
