#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef pthread_mutex_t	t_fork;

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
	t_params		*params;
	pthread_mutex_t	*speak_right;
	// int				**forks;
	// pthread_mutex_t	*eat_right;
	t_fork			*forks;
	struct timeval	*begining;
	int				i_philo;
	struct timeval	last_eat;
	struct timeval	action_begining;
	int				is_init;
	pthread_t		id;
	int				stop_when_possible;
	int				n_times_eaten;
	//
	int				can_take_forks;
}	t_philo;

typedef struct s_table
{
	t_params		params;
	pthread_mutex_t	speak_right;
	t_philo			*philos;
	int				*forks;
	// pthread_mutex_t	eat_right;
	struct timeval	beginning;
}	t_table;

// libft
void	ft_bzero(void *m, size_t size);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char *s);
void	*ft_calloc(size_t n, size_t size);

// main

void	tell_death(t_table *table, t_philo *p);
void	tell_end(t_table *table);

void	quit(t_table *table);
int		error_quit(t_table *table);

int		test_end(t_table *table, int i);
void	end_simulation(t_table *table);
int		launch_simulation(t_table *table);

// handle_args
int		invalid_numeric_arg(char *arg);
int		handle_args(int argc, char **argv, t_params *params);

// create_table
int		create_table(int argc, char **argv, t_table **table);

// philo_life_utils
void	say(t_philo *p, char *message);
void	take_fork(t_philo *p, int left);
void	putback_fork(t_philo *p, int left);
// void	take_forks(t_philo *p);
// void	putback_forks(t_philo *p);
void	take_fork(t_philo *p, int left);
void	putback_fork(t_philo *p, int left);

// time_utils
long	delta_time(struct timeval tv1, struct timeval tv2);
long	tick(t_philo *p);
long	tick_table(t_table *table);
int		has_died(t_philo *p);
void	corrected_sleep(int duration, struct timeval begining);

// philo_life
void	*philo_life(t_philo *p);

#endif
