/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:12:30 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:14:23 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == d)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (d == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
