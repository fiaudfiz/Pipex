/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:16:46 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:05:18 by miouali          ###   ########.fr       */
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

int	ft_putnbr_ptr(unsigned long long adress)
{
	char				*base;
	int					count;

	base = "0123456789abcdef";
	count = 0;
	if (adress >= 16)
		count += ft_putnbr_ptr(adress / 16);
	count += ft_putchar_one(base[adress % 16]);
	return (count);
}

int	ft_format_p(va_list ap)
{
	unsigned long long	adress;
	int					count;

	count = 0;
	adress = va_arg(ap, unsigned long long);
	if (adress == 0)
		return (ft_putstr("(nil)"));
	else
		count = ft_putstr("0x");
	count += ft_putnbr_ptr(adress);
	return (count);
}
