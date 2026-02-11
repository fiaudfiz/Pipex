/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:03:07 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:06:15 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar_one(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr_i(int number)
{
	int	count;

	count = 0;
	if (number == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (number < 0)
	{
		number = -number;
		ft_putchar_one('-');
		count = 1;
	}
	if (number > 9)
	{
		ft_putnbr_i(number / 10);
		ft_putnbr_i(number % 10);
	}
	else
		ft_putchar_one(number + 48);
	return (ft_size_base(number, 10) + count);
}

int	ft_format_i(va_list ap)
{
	int	number;

	number = va_arg(ap, int);
	return (ft_putnbr_i(number));
}
