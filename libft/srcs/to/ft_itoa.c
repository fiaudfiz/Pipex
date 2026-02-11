/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:03 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 09:58:31 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_write_int_min(char *dest, long min, int size)
{
	min = -min;
	dest[0] = '-';
	while (min > 0)
	{
		dest[size--] = '0' + min % 10;
		min = min / 10;
	}
	return (dest);
}

char	*ft_write_result(int n, char *dest, int size)
{
	while (n > 0)
	{
		dest[size--] = '0' + n % 10;
		n = n / 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		size;
	long	min;

	size = ft_size(n);
	min = -2147483648;
	dest = malloc ((sizeof(char) * size) + 1);
	if (!dest)
		return (NULL);
	dest[size--] = '\0';
	if (n == -2147483648)
		return (ft_write_int_min(dest, min, size));
	if (n == 0)
	{
		dest[0] = '0';
		return (dest);
	}
	if (n < 0)
	{
		n = -n;
		dest[0] = '-';
	}
	return (ft_write_result(n, dest, size));
}
