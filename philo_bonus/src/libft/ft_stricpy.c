/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:22:09 by lzins             #+#    #+#             */
/*   Updated: 2021/07/27 18:36:00 by lzins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static void	compute_digits(int n, int sgn, int *size, char *digits)
{
	int	i;

	if (n == 0)
	{
		*size = 1;
		digits[0] = '0';
		return ;
	}
	i = 0;
	while (n != 0)
	{
		digits[i] = '0' + sgn * (n % 10);
		n /= 10;
		i++;
	}
	*size = i;
}

static void	reverse_fill(char *s, char *digits, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		s[i] = digits[size - 1 - i];
		i++;
	}
}

void	ft_stricpy(char *str, int n)
{
	char	digits[10];
	int		sgn;
	int		size;

	if (n < 0)
		sgn = -1;
	else
		sgn = 1;
	compute_digits(n, sgn, &size, digits);
	reverse_fill(str, digits, size);
	str[size] = '\0';
}
