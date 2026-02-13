/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:16:56 by miouali           #+#    #+#             */
/*   Updated: 2026/02/13 13:55:04 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_error(char *error)
{
	perror(error);
	exit(1);
}

void	msg_error_path(char *error, int fd, int tab_fd[2])
{
	close(tab_fd[0]);
	close(tab_fd[1]);
	close(fd);		
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error, 2);
	exit(127);
}

int	check_arg(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	msg_error_fd(char *error, int fd[2])
{
	int	exit_status;

	if (errno == EACCES)
		exit_status = 126;
	else if (errno == ENOENT)
		exit_status = 127;
	else
		exit_status = 1;
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	perror(error);
	exit(exit_status);
}

void	msg_error_cmd(char *error, int fd, int tab_fd[2])
{
	close(fd);
	close (tab_fd[0]);
	close (tab_fd[1]);
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error, 2);
	exit(127);
}

void	msg_error_cmd_path(char *error, int fd, int tab_fd[2], char **cmd_tab)
{
	int exit_status;

	if (errno == EACCES)
		exit_status = 126;
	else if (errno == ENOENT)
		exit_status = 127;
	else
		exit_status = 1;
	close(fd);
	close(tab_fd[0]);
	close(tab_fd[1]);
	ft_free_str_tab(cmd_tab);
	perror(error);
	exit(exit_status);
}
void	msg_error_execve(char *error, char **cmd_tab, char *cmd_path)
{
	int	exit_code;

	ft_free_str_tab(cmd_tab);
	free(cmd_path);
	if (errno == EACCES || errno ==  EISDIR)
		exit_code = 126;
	else if (errno == ENOENT)
		exit_code = 127;
	else
		exit_code = 1;
	perror(error);
	exit(exit_code);
}