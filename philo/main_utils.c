#include "philosophers.h"

static int	usage_error(t_param **p)
{
	ft_putstr_fd("Error: Usage: ./philosophers n_philo t_die t_eat " \
		"t_sleep [n_times_eat]\n", STDERR_FILENO);
	free(*p);
	*p = NULL;
	return (-1);
}

static void	init_param_values(int argc, char **argv, t_param **p)
{
	(*p)->n_philo = ft_atoi(argv[1]);
	(*p)->t_die = ft_atoi(argv[2]);
	(*p)->t_eat = ft_atoi(argv[3]);
	(*p)->t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		(*p)->n_times_eat = -1;
	if (argc == 6)
		(*p)->n_times_eat = ft_atoi(argv[5]);
}

static int	invalid_param_values(int argc, char **argv, t_param **p)
{
	return ((*p)->n_philo < 0 || (*p)->t_die < 0 || (*p)->t_eat < 0
		|| (*p)->t_sleep < 0 || (argc == 6 && (*p)->n_times_eat < 0));
}


int	handle_args(int argc, char **argv, t_param **p)
{
	*p = NULL;
	if (argc != 5 && argc != 6)
		return (usage_error(p));
	*p = ft_calloc(1, sizeof(t_param));
	if (!*p)
		return (-1);
	init_param_values(argc, argv, p);
	if (invalid_param_values(argc, argv, p))
		return (usage_error(p));
	return (0);
}
