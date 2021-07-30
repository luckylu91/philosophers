#include "philosophers.h"

int	create_sem(char *name, sem_t **sem_addr, int value)
{
	sem_unlink(name);
	*sem_addr = sem_open(name, O_CREAT, 0666, value);
	if (!*sem_addr)
		return (-1);
	return (0);
}
