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

static void	init_param_values(int argc, char **argv, t_table *t)
{
	t->params.n_philo = ft_atoi(argv[1]);
	t->params.t_die = ft_atoi(argv[2]);
	t->params.t_eat = ft_atoi(argv[3]);
	t->params.t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		t->params.n_times_eat = -1;
	if (argc == 6)
		t->params.n_times_eat = ft_atoi(argv[5]);
}

static int	invalid_param_values(int argc, char **argv, t_table *t)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (invalid_numeric_arg(argv[i]))
			return (1);
	}
	return (t->params.n_philo <= 0 || t->params.t_die < 0 || t->params.t_eat < 0
		|| t->params.t_sleep < 0 || (argc == 6 && t->params.n_times_eat < 0));
}

int	handle_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (usage_error());
	init_param_values(argc, argv, table);
	if (invalid_param_values(argc, argv, table))
		return (value_error());
	return (0);
}
