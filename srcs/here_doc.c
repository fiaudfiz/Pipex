/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:46:31 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 14:47:47 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

int	execute_here_doc(int *fd_here_doc, char *lim_nl)
{
	char	*line;

	ft_printf("heredoc> ");
	line = get_next_line(0);
	if (!line || ft_strcmp(line, lim_nl) == 0)
	{
		free(line);
		return (1);
	}
	write(fd_here_doc[1], line, ft_strlen(line));
	free(line);
	return (0);
}

int	handle_here_doc(char *limiter)
{
	int		fd_here_doc[2];
	char	*lim_nl;

	if (pipe(fd_here_doc))
		return (-1);
	lim_nl = ft_strjoin(limiter, "\n");
	if (!lim_nl)
	{
		close(fd_here_doc[0]);
		close(fd_here_doc[1]);
		return (-1);
	}
	while (1)
	{
		if (execute_here_doc(fd_here_doc, lim_nl) == 1)
			break ;
	}
	free(lim_nl);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}
