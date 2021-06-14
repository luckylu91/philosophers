#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef pthread_mutex_t	t_fork;

typedef struct s_params
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_times_eat;
}	t_params;

typedef struct	s_philo
{
	t_params *params;
	pthread_mutex_t	*speak_right;
	int	i_philo;
	struct timeval	last_eat;
	struct timeval	*begining;
	int	is_init;
	int	is_eating;
	t_fork	*left;
	t_fork	*right;
	pthread_t	id;
	int	stop_when_possible;
	int n_times_eaten;
}	t_philo;

typedef struct s_table
{
	t_params	params;
	pthread_mutex_t	speak_right;
	t_philo			*philos;
	t_fork			*forks;
	struct timeval beginning;
}	t_table;

void	ft_bzero(void *m, size_t size);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char *s);
void	*ft_calloc(size_t n, size_t size);

void	quit(t_table *table);
int		error_quit(t_table *table);

int	invalid_numeric_arg(char *arg);
int	handle_args(int argc, char **argv, t_table *table);

void	say(t_philo *p, char *message);
void	take_fork(t_philo *p, int left);
void	putback_fork(t_philo *p, int left);

void	init_eat(t_philo *p);
long	tick(t_philo *p, struct timeval *tv);
int		finished_activity(t_philo *p, int t_activity);
int		has_died(t_philo *p);

int	create_table(int argc, char **argv, t_table **table);

void	*philo_life(t_philo *p);

#endif
