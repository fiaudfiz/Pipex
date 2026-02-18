/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:31:32 by miouali           #+#    #+#             */
/*   Updated: 2026/02/16 20:18:44 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

/*void	fork_sons(char *av, char **envp, int *fd, int fd_prev)
{
	char	**cmd_tab;
	char	*cmd_path;

	if (fd_prev == -1)
		msg_error_fd("Error in fd", fd);
	if (dup2(fd_prev, 0) == -1)
		msg_error_fd_bonus("Error in dup2", fd_prev);
	if (dup2(fd[1], 1) == -1)
		msg_error_fd_bonus("Error in dup2", fd[1]);
	close_fd(fd, fd_prev);
	cmd_tab = ft_split(av, ' ');
	if (check_arg(av) == 1)
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

int	loop_sons(char **av, int fd_prev, int *fd, char **envp)
{
	int		i;
	pid_t	pid;
	int		j;

	i = 2;
	j = 0;
	while (av[j])
		j++;
	while (i < j - 2)
	{
		if (pipe(fd) == -1)
			error_exit_parent("Error in Pipe", fd_prev, fd);
		pid = fork();
		if (pid == -1)
			error_exit_parent("Error in fork", fd_prev, fd);
		if (pid == 0)
			fork_sons(av[i], envp, fd, fd_prev);
		close(fd[1]);
		if(fd_prev >= 0)
			close(fd_prev);
		fd_prev = fd[0];
		i++;
	}
	return (fd_prev);
}

int	last_son(int fd_prev, int fd_out, char **envp, char *av)
{
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_tab;

	pid = fork();
	if (pid == -1)
			msg_error_fd_bonus("Error in fork",fd_prev);
	if (pid == 0)
	{
		if (fd_prev == -1)
			msg_error_fd_bonus("Error in fd", fd_out);
		if (dup2(fd_prev, 0) == -1) 
			msg_error_fd_bonus("Error in dup2", fd_prev);
		close(fd_prev);
		if (dup2(fd_out, 1) == -1)
			msg_error_fd_bonus("Error in dup2", fd_out);
		close(fd_out);
		cmd_tab = ft_split(av, ' ');
		if (check_arg(av) == 1)
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
	return (pid);
}
*/