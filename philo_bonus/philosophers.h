#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_params
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_times_eat;
}	t_params;

typedef struct s_philo
{
	int				i_philo;
	pid_t			id;
	struct timeval	last_eat;
	struct timeval	action_begining;
	int				n_times_eaten;
	int				stop_when_possible;
// shared :
	t_params		*params;
	sem_t			*speak_right;
	sem_t			*eat_queue;
	sem_t			*forks;
	sem_t			*death;
	struct timeval	*begining;
}	t_philo;

typedef struct s_table
{
	t_params		params;
	struct timeval	beginning;
	sem_t			*simulation_can_start;
	sem_t			*speak_right;
	sem_t			*eat_queue;
	sem_t			*forks;
	sem_t			*death;
	pid_t			*philos_pid;
	pid_t			death_watcher_pid;
}	t_table;

// utils
void	ft_bzero(void *m, size_t size);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char *s);
void	*ft_calloc(size_t n, size_t size);

long	delta_time(struct timeval tv1, struct timeval tv2);
long	tick(t_philo *p);
long	tick_table(t_table *table);
int		has_died(t_philo *p);
void	corrected_sleep(t_philo *p, int duration);

int		create_sem(char *name, sem_t **sem_addr, int value);

int		quit_main(t_table *t);
int		quit_others(t_table *t);
int		kill_and_quit(t_table *t);

int		create_table(int argc, char **argv, t_table *table);

// philo_life
void	philo_death(t_philo *p);
void	take_forks(t_philo *p);
void	putback_forks(t_philo *p);

void	say(t_philo *p, char *message);
void	tell_end(t_table *table);

void	philo_life(t_table *table, int i);

// main
int		invalid_numeric_arg(char *arg);
int		handle_args(int argc, char **argv, t_params *params);

void	watch_death(t_table *table);
int		launch_simulation(t_table *table);

#endif
