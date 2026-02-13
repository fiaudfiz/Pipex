/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:19:01 by miouali           #+#    #+#             */
/*   Updated: 2026/02/13 11:45:37 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

char	**get_path(char **envp)
{
	int		i;
	char	*temp;
	char	**path_tab;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
	{
		i++;
	}
	if (!envp[i])
		return (NULL);
	temp = envp[i];
	i = ft_strlen(temp);
	temp = ft_substr(temp, 5, i - 5);
	path_tab = ft_split(temp, ':');
	free(temp);
	return (path_tab);
}

char	*find_cmd_path(char **path, char **cmd_tab)
{
	int		i;
	char	*temp;

	i = 0;
	if (!path)
		return (NULL);
	if (!cmd_tab || !cmd_tab[0])
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		temp = ft_strjoin_free(temp, cmd_tab[0], 1);
		if (access(temp, F_OK | X_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

char	*cmd_with_path(char **cmd_tab, char **envp, int fd, int tab_fd[2])
{
	char	**path;
	char	*cmd_path;

	path = get_path(envp);
	if (!path)
		msg_error_path("Invalid Path", fd, tab_fd);
	cmd_path = find_cmd_path(path, cmd_tab);
	if (!cmd_path || !cmd_tab[0])
	{
		free(path);
		ft_free_str_tab(cmd_tab);
		msg_error_cmd("Command not found", fd, tab_fd);
		return (NULL);
	}
	return (cmd_path);
}

void	close_fd(int *fd_pipe, int fd)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close (fd);
}

void	first_son(char **av, char **envp, int *fd)
{
	char	*cmd_path;
	char	**cmd_tab;
	int		fd_in;

	fd_in = open(av[1], O_RDONLY); //on ouvre le fichier
	if (fd_in < 0)
		msg_error_fd(av[1], fd);
	cmd_tab = ft_split(av[2], ' ');
	if (check_arg(av[2]) == 1) // pas de /
		cmd_path = cmd_with_path(cmd_tab, envp, fd_in, fd);
	else //chemin relatif
	{
		cmd_path = ft_strdup(cmd_tab[0]);
		if (!(access(cmd_path, F_OK | X_OK) == 0))
			msg_error_cmd_path("Command path is incorrect", fd_in, fd, cmd_tab);
	}
	dup2(fd_in, 0); //dup2(nouveau, ancien) donc STDIN est maintenant le fichier
	dup2(fd[1], 1); //le STDOUT est maintenant l'entree du pipe
	close_fd(fd, fd_in);
	if (execve(cmd_path, cmd_tab, envp) == -1)
	{
		ft_free_str_tab(cmd_tab);
		free(cmd_path);
		msg_error("Execve");
	}
}
