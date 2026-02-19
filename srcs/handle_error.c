/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:45:44 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 14:46:23 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

void	close_fds(t_pipex *pipex)
{
	if (pipex->fd_prev > 2)
		close(pipex->fd_prev);
	if (pipex->fd_out > 2)
		close (pipex->fd_out);
	if (pipex->fd[0] > 2)
		close(pipex->fd[0]);
	if (pipex->fd[1] > 2)
		close(pipex->fd[1]);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->cmd_tab)
		ft_free_str_tab(pipex->cmd_tab);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	if (pipex->cmd_path2)
		free(pipex->cmd_path2);
}

void	error_struct(t_pipex *pipex, char *error, int exit_code)
{
	perror(error);
	close_fds(pipex);
	free_pipex(pipex);
	exit(exit_code);
}
