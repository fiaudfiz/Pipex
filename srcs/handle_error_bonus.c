#include "pipex.h"

void	msg_error_path_bonus(char *error)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error, 2);
	exit(127);
}
void	msg_error_cmd_path_bonus(char *error, char **cmd_tab)
{
	int exit_status;

	if (errno == EACCES)
		exit_status = 126;
	else if (errno == ENOENT)
		exit_status = 127;
	else
		exit_status = 1;
	ft_free_str_tab(cmd_tab);
	perror(error);
	exit(exit_status);
}

void	msg_error_cmd_bonus(char *error)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error, 2);
	exit(127);
}

void	msg_error_fd_bonus(char *error, int fd)
{
	close(fd);
	perror(error);
	exit(1);
}