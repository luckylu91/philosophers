#include "libft.h"

void	ft_bzero(void *m, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((unsigned char *)m)[i++] = 0;
}
