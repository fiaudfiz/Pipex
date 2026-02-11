/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:17:09 by miouali           #+#    #+#             */
/*   Updated: 2026/02/05 14:38:43 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_to_stash(int fd, char *stash)
{
	int			bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;

	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr_gnl(stash, '\n') != 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin_gnl(stash, buffer);
		free(stash);
		stash = tmp;
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		line = ft_substr_gnl(stash, 0, i + 1);
	else
		line = ft_substr_gnl(stash, 0, i);
	return (line);
}

static char	*get_new_stash(char *stash)
{
	int		i;
	char	*tmp;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	tmp = ft_substr_gnl(stash, i + 1, ft_strlen_gnl(stash));
	free(stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	stash = get_new_stash(stash);
	return (line);
}

/*#include <fcntl.h>
#include  <stdio.h> // Pour open

int main()
{
	char *line;
	int    fd;
	int i;

	i = 0;
	while (i < 6)
	{
		fd = open("test.bi", O_RDONLY);
		line = get_next_line(fd);
		printf ("%s", line);
		free (line);
    	i++;
	}
}*/
