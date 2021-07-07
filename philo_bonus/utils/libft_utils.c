#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

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

void	*ft_calloc(size_t n, size_t size)
{
	void	*res;

	res = malloc(n * size);
	if (res)
		memset(res, 0, n * size);
	return (res);
}

void	ft_bzero(void *m, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((unsigned char *)m)[i++] = 0;
}
