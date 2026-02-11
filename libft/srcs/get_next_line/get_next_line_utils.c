/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:50:32 by miouali           #+#    #+#             */
/*   Updated: 2026/02/05 14:38:07 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_gnl(char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == d)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen_gnl(const char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lens;
	char	*dest;

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
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static size_t	ft_strcpy_len(char *dest, const char *str, size_t i)
{
	size_t	j;

	j = 0;
	if (!str)
		return (i);
	while (str[j])
	{
		dest[i++] = str[j++];
	}
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1)+ ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = ft_strcpy_len(dest, s1, i);
	i = ft_strcpy_len(dest, s2, i);
	dest[i] = '\0';
	return (dest);
}
