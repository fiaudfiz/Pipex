/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:28:44 by miouali           #+#    #+#             */
/*   Updated: 2026/02/15 11:30:53 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		fd_prev;
	int		fd[2];
	int		fd_out;
	int		status;

	if (ac < 5)
		return (0);
	fd_prev = open(av[1], O_RDONLY);
	if (fd_prev < 0)
		msg_error(av[1]);
	fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		msg_error_fd_bonus(av[ac - 1], fd_prev);
	fd_prev = loop_sons(av, fd_prev, fd, envp);
	last_son(fd_prev, fd_out, envp, av[ac - 2]);
	close(fd_prev);
	close (fd_out);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
