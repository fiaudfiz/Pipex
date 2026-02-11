/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_son.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:50:53 by miouali           #+#    #+#             */
/*   Updated: 2026/02/09 14:23:57 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

void	second_son(char **av, char **envp, int *fd)
{
	char	*cmd_path;
	char	**cmd_tab;
	int		fd_out;

	cmd_tab = ft_split(av[3], ' ');
	if (check_arg(av[3]) == 1)
		cmd_path = cmd_with_path(cmd_tab, envp);
	else
	{
		cmd_path = cmd_tab[0];
		if (!(access(cmd_path, F_OK | X_OK) == 0))
			msg_error("Command path is incorrect");
	}
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		msg_error(av[4]);
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close_fd(fd, fd_out);
	if (execve(cmd_path, cmd_tab, envp) == -1)
	{
		ft_free_str_tab(cmd_tab);
		free(cmd_path);
		msg_error("Execve");
	}
}
