/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_big_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:10:07 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:07:18 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar_one(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

static int	ft_recursive_putnbr(unsigned int number)
{
	char				*base;
	int					count;

	base = "0123456789ABCDEF";
	count = 0;
	if (number >= 16)
	{
		count += ft_recursive_putnbr(number / 16);
	}
	count += ft_putchar_one(base[number % 16]);
	return (count);
}

int	ft_format_big_x(va_list ap)
{
	unsigned int	number;
	int				count;

	count = 0;
	number = va_arg(ap, unsigned int);
	if (number == 0)
		return (ft_putstr("0"));
	count += ft_recursive_putnbr(number);
	return (count);
}
