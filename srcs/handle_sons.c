/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:59 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 14:53:20 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

void	fork_sons_struct(t_pipex *pipex, int index)
{
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	if (dup2(pipex->fd_prev, 0) == -1)
		error_struct(pipex, "dup2", 1);
	if (dup2(pipex->fd[1], 1) == -1)
		error_struct(pipex, "dup2", 1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->fd_prev);
	pipex->cmd_tab = ft_split(pipex->av[index], ' ');
	if (check_arg(pipex->av[index]) == 1)
		pipex->cmd_path = cmd_with_path(pipex);
	else
	{
		if (!pipex->cmd_tab || !pipex->cmd_tab[0])
			error_struct(pipex, "Command not found", 127);
		pipex->cmd_path = ft_strdup(pipex->cmd_tab[0]);
		if (!(access(pipex->cmd_path, F_OK | X_OK) == 0))
			error_struct(pipex, "Command path is incorrect", 127);
	}
	if (!pipex->cmd_path)
		error_struct(pipex, "Command not found", 127);
	if (execve(pipex->cmd_path, pipex->cmd_tab, pipex->envp) == -1)
		error_struct(pipex, "Execve", 127);
}

void	loop_sons_struct(t_pipex *pipex)
{
	int	i;

	i = pipex->start_cmd;
	while (i < pipex->nbr_cmd - 1)
	{
		if (pipe(pipex->fd) == -1)
			error_struct(pipex, "Error in Pipe", 1);
		pipex->pid = fork();
		if (pipex->pid == -1)
			error_struct(pipex, "Error in fork", 1);
		if (pipex->pid == 0)
			fork_sons_struct(pipex, i);
		close(pipex->fd[1]);
		if (pipex->fd_prev != -1)
			close(pipex->fd_prev);
		pipex->fd_prev = pipex->fd[0];
		i++;
	}
}

static void	handle_last_redirections(t_pipex *pipex)
{
	int	dev_null;

	if (pipex->fd_prev == -1 || dup2(pipex->fd_prev, 0) == -1)
		error_struct(pipex, "dup2", 1);
	if (pipex->fd_out == -1)
	{
		dev_null = open("/dev/null", O_WRONLY);
		if (dev_null == -1 || dup2(dev_null, 1) == -1)
			error_struct(pipex, pipex->av[pipex->nbr_cmd], 1);
		close(dev_null);
	}
	else if (dup2(pipex->fd_out, 1) == -1)
		error_struct(pipex, "dup2", 1);
	close(pipex->fd_prev);
	if (pipex->fd_out > 2)
		close(pipex->fd_out);
}

static void	execute_last_cmd(t_pipex *pipex)
{
	pipex->cmd_tab = ft_split(pipex->av[pipex->nbr_cmd - 1], ' ');
	if (check_arg(pipex->av[pipex->nbr_cmd - 1]) == 1)
		pipex->cmd_path = cmd_with_path(pipex);
	else
	{
		if (!pipex->cmd_tab || !pipex->cmd_tab[0])
			error_struct(pipex, "Command not found", 127);
		pipex->cmd_path = ft_strdup(pipex->cmd_tab[0]);
		if (!pipex->cmd_path)
			error_struct(pipex, "Malloc failed", 1);
		if (!(access(pipex->cmd_path, F_OK | X_OK) == 0))
			error_struct(pipex, "Command path is incorrect", 127);
	}
	if (!pipex->cmd_path)
		error_struct(pipex, "Command not found", 127);
	if (execve(pipex->cmd_path, pipex->cmd_tab, pipex->envp) == -1)
		error_struct(pipex, "Execve", 127);
}

pid_t	last_son_struct(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		error_struct(pipex, "Error in fork", 1);
	if (pipex->pid == 0)
	{
		handle_last_redirections(pipex);
		execute_last_cmd(pipex);
	}
	return (pipex->pid);
}
