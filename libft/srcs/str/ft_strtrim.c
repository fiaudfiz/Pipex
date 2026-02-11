/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:59:00 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:18:52 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

void	get_bounds(const char *s, const char *set, int *start, int *end)
{
	int	len;

	*start = 0;
	while (s[*start] && in_set(s[*start], set))
		(*start)++;
	len = 0;
	while (s[len])
		len++;
	*end = len - 1;
	while (*end >= *start && in_set(s[*end], set))
		(*end)--;
}

char	*copy_range(const char *s, int start, int end)
{
	int		i;
	char	*res;

	if (start > end)
	{
		res = malloc(1);
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	res = malloc(end - start + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

char	*ft_strtrim(const char *s, const char *set)
{
	int	start;
	int	end;

	get_bounds(s, set, &start, &end);
	return (copy_range(s, start, end));
}
