/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:12:22 by miouali           #+#    #+#             */
/*   Updated: 2026/02/13 14:42:44 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"



int	main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	int		fd[2]; //entre et sortie du pipe
	if (ac < 5)
		return (0);
	if (pipe(fd) == -1) // cree un pipe
		msg_error("Pipe");
	pid1 = fork();
	if (pid1 == 0)
		first_son(av, envp, fd);
	pid2 = fork();
	if (pid2 == 0)
		second_son(av, envp, fd);
	close(fd[0]); // Très important
	close(fd[1]); // Très important
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status , 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
