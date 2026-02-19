/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:48:30 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 14:48:51 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

void	struct_init(char **av, int ac, t_pipex *pipex, char **envp)
{
	pipex->av = av;
	pipex->envp = envp;
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
