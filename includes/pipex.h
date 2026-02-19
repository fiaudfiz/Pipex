/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:37:13 by miouali           #+#    #+#             */
/*   Updated: 2026/02/19 14:43:48 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/includes/libft.h"

typedef struct s_pipex
{
	int		fd_prev;
	int		fd_out;
	int		status;
	pid_t	last_pid;
	pid_t	pid;
	int		here_doc;
	int		nbr_cmd;
	char	**av;
	char	**envp;
	int		start_cmd;
	int		fd[2];
	char	*cmd_path;
	char	**cmd_tab;
	char	**path;
	char	*cmd_path2;
	int		exit_code;
}	t_pipex;

char	**get_path(char **envp);
char	*find_cmd_path(char **path, char **cmd_tab);
int		check_arg(char *cmd);
char	*cmd_with_path(t_pipex *pipex);
int		handle_here_doc(char *limiter);
void	close_fds(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
void	error_struct(t_pipex *pipex, char *error, int exit_code);
void	struct_init(char **av, int ac, t_pipex *pipex, char **envp);
void	fork_sons_struct(t_pipex *pipex, int index);
void	loop_sons_struct(t_pipex *pipex);
pid_t	last_son_struct(t_pipex *pipex);
void	struct_init_bonus(char **av, int ac, t_pipex *pipex, char **envp);

#endif
