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

typedef struct s_param
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_times_eat;
	int	i_philo;
	struct timeval	last_eat;
	struct timeval	begining;
	int	is_init;
	int	is_eating;
	t_fork	*left;
	t_fork	*right;
	pthread_mutex_t	speak_right;
	pthread_t	id;
	int	stop_when_possible;
}	t_param;

typedef struct s_table
{
	int		n_philo;
	t_param	*philos;
	t_fork	*forks;
}	t_table;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char *s);
void	*ft_calloc(size_t n, size_t size);

void	quit(t_param *p, t_fork *forks);
int		error_quit(t_param *p, t_fork *forks);

int		handle_args(int argc, char **argv, t_param **p);

void	say(t_param *p, char *message, int keep_lock);
void	take_fork(t_param *p, int left);
void	putback_fork(t_param *p, int left);

void	init_eat(t_param *p);
long	tick(t_param *p, struct timeval *tv);
int		finished_activity(t_param *p, int t_activity);
int		has_died(t_param *p);


int		create_table(int argc, char **argv, t_param **p, t_fork **forks);
// int		duplicate_param(t_param **p);
// int		create_forks(int n_philo, t_fork **forks_array);
// void	distrubute_forks(t_param *p_array, t_fork *forks_array);

void	*philo_life(t_param *p);

#endif
