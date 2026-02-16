/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sons.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:50:53 by miouali           #+#    #+#             */
/*   Updated: 2026/02/16 19:21:54 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

void	second_son(char **av, char **envp, int *fd)
{
	char	*cmd_path;
	char	**cmd_tab;
	int		fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		msg_error_fd(av[4], fd);
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close_fd(fd, fd_out);
	cmd_tab = ft_split(av[3], ' ');
	if (check_arg(av[3]) == 1)
		cmd_path = cmd_with_path(cmd_tab, envp);
	else
	{
		cmd_path = ft_strdup(cmd_tab[0]);
		if (!(access(cmd_path, F_OK | X_OK) == 0))
			msg_error_std("Command path is incorrect", cmd_tab, cmd_path);
	}
	if (execve(cmd_path, cmd_tab, envp) == -1)
		msg_error_std("Execve", cmd_tab, cmd_path);
}

void	first_son(char **av, char **envp, int *fd)
{
	char	*cmd_path;
	char	**cmd_tab;
	int		fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
	{
		msg_error_fd(av[1], fd);
		exit(1);
	}
	dup2(fd_in, 0);
	dup2(fd[1], 1);
	close_fd(fd, fd_in);
	cmd_tab = ft_split(av[2], ' ');
	if (check_arg(av[2]) == 1)
		cmd_path = cmd_with_path(cmd_tab, envp);
	else
	{
		cmd_path = ft_strdup(cmd_tab[0]);
		if (!(access(cmd_path, F_OK | X_OK) == 0))
			msg_error_std("Command path is incorrect", cmd_tab, cmd_path);
	}
	if (execve(cmd_path, cmd_tab, envp) == -1)
		msg_error_std("Execve", cmd_tab, cmd_path);
}
