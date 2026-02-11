/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:35:45 by miouali           #+#    #+#             */
/*   Updated: 2026/02/05 09:31:48 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse(char *str)
{
	int	index;

	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		write(1, &str[index], 1);
		index--;
	}
}

static void	ft_fill_base(long n, char *base, int len, char *res)
{
	int	i;

	i = 0;
	if (n == 0)
		res[i++] = base[0];
	while (n > 0)
	{
		res[i++] = base[n % len];
		n /= len;
	}
	res[i] = '\0';
}

int	ft_check_base(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' || str[i] == '-' || str[i] <= 32 || str[i] > 126)
			return (1);
		j = i;
		while (str[++j])
			if (str[i] == str[j])
				return (1);
	}
	return (0);
}

int	ft_putnbr_base(int n, char *base)
{
	long	nb;
	int		len;
	char	*res;
	int		final_len;

	len = ft_strlen(base);
	if (len <= 1 || ft_check_base(base))
		return (0);
	nb = n;
	final_len = ft_size_base(n, len);
	res = ft_calloc(sizeof(char), final_len + 1);
	if (!res)
		return (0);
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	ft_fill_base(nb, base, len, res);
	ft_reverse(res);
	free(res);
	return (final_len);
}
