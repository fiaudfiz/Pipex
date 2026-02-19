/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:12:22 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 17:25:30 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		return (1);
	ft_memset(&pipex, 0, sizeof(t_pipex));
	struct_init(av, ac, &pipex, envp);
	loop_sons_struct(&pipex);
	pipex.last_pid = last_son_struct(&pipex);
	if (pipex.fd_prev != -1)
		close(pipex.fd_prev);
	if (pipex.fd_out != -1)
		close (pipex.fd_out);
	waitpid(pipex.last_pid, &pipex.status, 0);
	while (wait(NULL) > 0)
		;
	if (pipex.fd_out == -1)
		pipex.exit_code = 1;
	else if (WIFEXITED(pipex.status))
		pipex.exit_code = WEXITSTATUS(pipex.status);
	else
		pipex.exit_code = 0;
	return (pipex.exit_code);
}
