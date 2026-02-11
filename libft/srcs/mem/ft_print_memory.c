/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:11:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/04 15:13:20 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_puthex_byte(unsigned char c)
{
	char	*base;

	base = "0123456789abcdef";
	write(1, &base[c / 16], 1);
	write(1, &base[c % 16], 1);
}

static void	ft_print_line(unsigned char *ptr, unsigned int size, unsigned int i)
{
	unsigned int	j;

	ft_puthex_byte((i >> 8) & 0xFF);
	ft_puthex_byte(i & 0xFF);
	write(1, ": ", 2);
	j = -1;
	while (++j < 16)
	{
		if (i + j < size)
			ft_puthex_byte(ptr[i + j]);
		else
			write(1, "  ", 2);
		if (j % 2 != 0)
			write(1, " ", 1);
	}
	j = -1;
	while (++j < 16)
	{
		if (i + j < size && ptr[i + j] >= 32 && ptr[i + j] <= 126)
			write(1, &ptr[i + j], 1);
		else if (i + j < size)
			write(1, ".", 1);
	}
	write(1, "\n", 1);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		ft_print_line((unsigned char *)addr, size, i);
		i += 16;
	}
	return (addr);
}
