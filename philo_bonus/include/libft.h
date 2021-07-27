#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t n, size_t size);
void	ft_bzero(void *m, size_t size);
int		ft_atoi(char *s);
char	*ft_stpcpy(char *dest, char *src);
void	ft_stricpy(char *str, int n);

#endif
