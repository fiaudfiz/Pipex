/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:16:56 by miouali           #+#    #+#             */
/*   Updated: 2026/02/14 11:06:01 by miouali          ###   ########.fr       */
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