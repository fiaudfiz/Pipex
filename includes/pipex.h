#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/includes/libft.h"

void	msg_error(char *error);
void	msg_error_path(char *error);
char	**get_path(char **envp);
char	*find_cmd_path(char **path, char **cmd_tab);
void	first_son(char **av, char **envp, int *fd);
void	second_son(char **av, char **envp, int *fd);
int		check_arg(char *cmd);
void	close_fd(int *fd_pipe, int fd);
char	*cmd_with_path(char **cmd_tab, char **envp);

#endif