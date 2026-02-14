#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd_prev;
	int	i;
	pid_t	pid;
	int		fd[2];
	char	*cmd_path;
	char	**cmd_tab;
	int		fd_out;
	int		status;

	if (ac < 5)
		return (0);
	i = 2;
	fd_prev = open(av[1], O_RDONLY);
	if (fd_prev < 0)
		msg_error(av[1]);
	while (i < ac - 2)
	{
		if (pipe(fd) == -1)
			msg_error("Pipe");
		pid = fork();
		if (pid == 0)
		{	
			dup2(fd_prev, 0);
			dup2(fd[1], 1);
			close_fd(fd, fd_prev);
			cmd_tab = ft_split(av[i], ' ');
			if (check_arg(av[i]) == 1) // pas de /
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
		close(fd[1]);
		close(fd_prev);
		fd_prev = fd[0];
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		fd_out = open(av[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			msg_error_fd_bonus(av[i + 1], fd[0]);
		dup2(fd_prev, 0);
		dup2(fd_out, 1);
		close(fd_prev);
        close(fd_out);
		cmd_tab = ft_split(av[i], ' ');
		if (check_arg(av[i]) == 1)
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
	close(fd_prev); // Très important
	while (wait(&status) > 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}