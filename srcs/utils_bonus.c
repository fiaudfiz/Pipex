#include "pipex.h"
#include "../libft/includes/libft.h"

void	fork_sons(char *av, char **envp, int *fd, int fd_prev)
{
	char **cmd_tab;
	char *cmd_path;

	dup2(fd_prev, 0);
	dup2(fd[1], 1);
	close_fd(fd, fd_prev);
	cmd_tab = ft_split(av, ' ');
	if (check_arg(av) == 1) // pas de /
		cmd_path = cmd_with_path(cmd_tab, envp);
	else //chemin relatif
	{
		cmd_path = ft_strdup(cmd_tab[0]);
		if (!(access(cmd_path, F_OK | X_OK) == 0))
			msg_error_standart("Command path is incorrect", cmd_tab, cmd_path);
	}
	if (execve(cmd_path, cmd_tab, envp) == -1)
		msg_error_standart("Execve", cmd_tab, cmd_path);
}

int	loop_sons(char **av, int fd_prev, int *fd, char **envp)
{
	int	i;
	pid_t	pid;
	int	j;

	i = 2;
	j = 0;
	while (av[j])
		j++;
	while (i < j - 2)
	{
		if (pipe(fd) == -1)
			msg_error("Pipe");
		pid = fork();
		if (pid == 0)
			fork_sons(av[i], envp, fd, fd_prev);
		close(fd[1]);
		close(fd_prev);
		fd_prev = fd[0];
		i++;
	}
	return (fd_prev);
}

void	last_son(int fd_prev, int fd_out, char  **envp, char *av)
{
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_tab;

	pid = fork(); //fd_prev fd_out envp &av
	if (pid == 0)
	{
		dup2(fd_prev, 0);
		dup2(fd_out, 1);
		close(fd_prev);
        close(fd_out);
		cmd_tab = ft_split(av, ' ');
		if (check_arg(av) == 1)
			cmd_path = cmd_with_path(cmd_tab, envp);
		else
		{
			cmd_path = ft_strdup(cmd_tab[0]);
			if (!(access(cmd_path, F_OK | X_OK) == 0))
				msg_error_standart("Command path is incorrect", cmd_tab, cmd_path);
		}
		if (execve(cmd_path, cmd_tab, envp) == -1)
			msg_error_standart("Execve", cmd_tab, cmd_path);
	}
}
