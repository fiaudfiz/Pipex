/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:16:56 by miouali           #+#    #+#             */
/*   Updated: 2026/02/15 12:01:33 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_error(char *error)
{
	perror(error);
	exit(1);
}

void	msg_error_fd(char *error, int fd[2])
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	perror(error);
	exit(1);
}

void	msg_error_std(char *error, char **cmd_tab, char *cmd_path)
{
	int	exit_code;

	ft_free_str_tab(cmd_tab);
	free(cmd_path);
	if (errno == EACCES || errno == EISDIR)
		exit_code = 126;
	else if (errno == ENOENT)
		exit_code = 127;
	else
		exit_code = 1;
	perror(error);
	exit(exit_code);
}

void	msg_error_cmd(char *error)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error, 2);
	exit(127);
}

void	msg_error_fd_bonus(char *error, int fd)
{
	if (fd)
		close(fd);
	perror(error);
	exit(1);
}

void	error_exit_parent(char *error, int fd_prev, int *fd)
{
	perror(error);
	if (fd_prev != -1)
		close(fd_prev);
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	exit(1);
}
void	msg_error_fd_out(void)
{
	ft_putstr_fd("out: Permission denied\n", 2);
	exit (1);
}