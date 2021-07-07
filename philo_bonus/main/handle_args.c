#include "philosophers.h"

static int	usage_error(void)
{
	ft_putstr_fd("Error (Usage)\n\tpath/to/philo n_philo t_die t_eat " \
		"t_sleep [n_times_eat]\n", STDERR_FILENO);
	return (-1);
}

static int	value_error(void)
{
	ft_putstr_fd("Error (Value)\n\tOne of the arguments has an invalid value, " \
		"n_philo >= 1, other values >= 0\n", STDERR_FILENO);
	return (usage_error());
}

static void	init_param_values(int argc, char **argv, t_params *p)
{
	p->n_philo = ft_atoi(argv[1]);
	p->t_die = ft_atoi(argv[2]);
	p->t_eat = ft_atoi(argv[3]);
	p->t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		p->n_times_eat = -1;
	if (argc == 6)
		p->n_times_eat = ft_atoi(argv[5]);
}

static int	invalid_param_values(int argc, char **argv, t_params *p)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (invalid_numeric_arg(argv[i]))
			return (1);
	}
	return (p->n_philo <= 0 || p->t_die < 0 || p->t_eat < 0
		|| p->t_sleep < 0 || (argc == 6 && p->n_times_eat < 0));
}

int	handle_args(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
		return (usage_error());
	init_param_values(argc, argv, params);
	if (invalid_param_values(argc, argv, params))
		return (value_error());
	return (0);
}
