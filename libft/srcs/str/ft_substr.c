/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:18:31 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:18:40 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	lens;

	lens = 0;
	if (!s)
		return (NULL);
	while (s[lens])
		lens++;
	i = 0;
	if (start >= lens)
		len = 0;
	if (len > lens - start)
		len = lens - start;
	dest = ft_calloc(len + 1, 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	return (dest);
}
