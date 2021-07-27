#include "libft.h"

int	ft_atoi(char *s)
{
	long	res;

	res = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		res = res * 10 + *s - '0';
		if (res > INT_MAX)
			return (INT_MAX);
		s++;
	}
	return (res);
}
