/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:55:46 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 14:56:54 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct_here_doc(char **av, int ac, t_pipex *pipex)
{
	pipex->here_doc = 1;
	pipex->nbr_cmd = ac - 1;
	pipex->fd_prev = handle_here_doc(av[2]);
	if (pipex->fd_prev == -1)
		error_struct(pipex, av[1], 1);
	pipex->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	pipex->start_cmd = 3;
}

void	struct_init_bonus(char **av, int ac, t_pipex *pipex, char **envp)
{
	pipex->av = av;
	pipex->envp = envp;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		init_struct_here_doc(av, ac, pipex);
	else
	{
		pipex->here_doc = 0;
		pipex->nbr_cmd = ac - 1;
		pipex->start_cmd = 2;
		pipex->fd_prev = open(av[1], O_RDONLY);
		if (pipex->fd_prev < 0)
		{
			perror (av[1]);
			pipex->fd_prev = open ("/dev/null", O_RDONLY);
		}
		pipex->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_out < 0)
			perror(av[ac - 1]);
	}
}
