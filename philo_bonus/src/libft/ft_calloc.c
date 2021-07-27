#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*res;

	res = malloc(n * size);
	if (res)
		memset(res, 0, n * size);
	return (res);
}
