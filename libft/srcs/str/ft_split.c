/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:12:18 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:14:06 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **dest, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}

static char	*ft_strndup_simple(const char *s, size_t size)
{
	char	*dup;
	size_t	i;

	dup = malloc(size + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;
	int	flag;

	i = 0;
	word = 0;
	while (s[i])
	{
		flag = 0;
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			flag = 1;
		}
		if (flag)
			word++;
	}
	return (word);
}

static char	**ft_fill_tab(char **dest, char const *s, char c)
{
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		dest[j] = ft_strndup_simple(&s[i], len);
		if (!dest[j])
			return (ft_free(dest, j - 1));
		j++;
		i += len;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_word(s, c);
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (NULL);
	if (!ft_fill_tab(dest, s, c))
		return (NULL);
	return (dest);
}

/*
int main(void)
{
    char **result;
    int i = 0;
    result = ft_split("cccccccchello", 'c');
    if (!result)
    {
        printf("Erreur : ft_split a renvoyé NULL\n");
        return 1;
    }
    while (result[i])
    {
        printf("mot %d : %s\n", i, result[i]);
        i++;
    }
    if (i == 0)
        printf("Aucun mot trouvé, tableau vide\n");
    i = 0;
    while (result[i])
        free(result[i++]);
    free(result);

    return 0;
}*/
