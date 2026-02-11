/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:41:59 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 09:29:56 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*
int	main()
{
	char test[] = "aaaaaaaa";
	int	i;

	i = 0;
	ft_bzero(test, 3);
	while (i < 9)
	{
		printf("%d\n" , test[i]);
		i++;
	}
	return (0);
}*/