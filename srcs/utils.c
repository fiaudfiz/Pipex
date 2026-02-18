/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:19:01 by miouali           #+#    #+#             */
/*   Updated: 2026/02/16 20:20:03 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

/*int	check_arg(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

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

char	*cmd_with_path(char **cmd_tab, char **envp)
{
	char	**path;
	char	*cmd_path;

	path = get_path(envp);
	if (!path)
		msg_error_cmd("Invalid Path");
	cmd_path = find_cmd_path(path, cmd_tab);
	ft_free_str_tab(path);
	if (!cmd_path || !cmd_tab[0])
	{
		ft_free_str_tab(cmd_tab);
		msg_error_cmd("Command not found");
		return (NULL);
	}
	return (cmd_path);
}*/

void	close_fd(int *fd_pipe, int fd)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close (fd);
}
