#include "pipex.h"
#include "../libft/includes/libft.h"

int	check_arg(char *cmd)
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
    if (!temp)
        return (NULL);
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
        if (!temp)
            return (NULL);
		temp = ft_strjoin_free(temp, cmd_tab[0], 1);
        if (!temp)
            return (NULL);
		if (access(temp, F_OK | X_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

char *cmd_with_path(t_pipex *pipex)
{
    pipex->path = get_path(pipex->envp);
    if (!pipex->path)
        error_struct(pipex, "Invalid Path", 1); //erreur ici de renvoi
    pipex->cmd_path2 = find_cmd_path(pipex->path, pipex->cmd_tab);
    ft_free_str_tab(pipex->path);
    if (!pipex->cmd_tab || !pipex->cmd_tab[0])
    {
        error_struct(pipex, "Command not found", 127);
        return (NULL);
    }   
    return (pipex->cmd_path2);
}