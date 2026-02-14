#include "pipex.h"
#include "../libft/includes/libft.h"

void	loop_sons(char *av, char **envp, int *fd, int fd_prev)
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
