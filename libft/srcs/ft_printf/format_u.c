/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:27:28 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 09:30:29 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_u(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr_core(unsigned int number)
{
	int	count;

	count = 0;
	if (number > 9)
	{
		count += ft_putnbr_core(number / 10);
	}
	ft_putchar_u(number % 10 + '0');
	count++;
	return (count);
}

int	ft_format_u(va_list ap)
{
	unsigned int	number;

	number = va_arg(ap, unsigned int);
	if (number == 0)
	{
		return (ft_putchar_u('0'));
	}
	return (ft_putnbr_core(number));
}
