/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:10:43 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:06:47 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar_one(char c)
{
	write(1, &c, 1);
	return (1);
}

bool	par_sing(const char *format)
{
	int		i;
	char	c;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (1);
			c = format[i + 1];
			if (!(c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
					|| c == 'u' || c == 'x' || c == 'X' || c == '%'))
				return (1);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}

int	ft_printf_format(char c, va_list args)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (g_format_tab[i].letter != 0)
	{
		if (g_format_tab[i].letter == c)
		{
			count += g_format_tab[i].format_alias(args);
			return (count);
		}
		else
			i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		j;
	int		count;

	j = 0;
	count = 0;
	va_start(args, format);
	if (par_sing(format) != 0)
		return (-1);
	while (format[j] != '\0')
	{
		if (format[j] == '%' && format[j + 1] != '\0')
		{
			count += ft_printf_format(format[j + 1], args);
			if (format[j + 2] != '\0')
				j = j + 2;
			else
				return (count);
		}
		else
			count += ft_putchar_one(format[j++]);
	}
	va_end(args);
	return (count);
}
