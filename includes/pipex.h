/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:37:13 by miouali           #+#    #+#             */
/*   Updated: 2026/02/15 11:37:41 by miouali          ###   ########.fr       */
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

char	**get_path(char **envp);
char	*find_cmd_path(char **path, char **cmd_tab);
void	first_son(char **av, char **envp, int *fd);
void	second_son(char **av, char **envp, int *fd);
int		check_arg(char *cmd);
void	close_fd(int *fd_pipe, int fd);
char	*cmd_with_path(char **cmd_tab, char **envp);
void	msg_error_std(char *error, char **cmd_tab, char *cmd_path);
void	msg_error(char *error);
void	msg_error_cmd(char *error);
void	msg_error_fd_bonus(char *error, int fd);
void	msg_error_fd(char *error, int fd[2]);
void	fork_sons(char *av, char **envp, int *fd, int fd_prev);
int		loop_sons(char **av, int fd_prev, int *fd, char **envp);
void	last_son(int fd_prev, int fd_out, char **envp, char *av);

#endif
