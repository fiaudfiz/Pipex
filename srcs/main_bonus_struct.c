#include "pipex.h"
#include "../libft/includes/libft.h"

int     handle_here_doc(char *limiter)
{
    int fd_here_doc[2];
    char *line;
    char *lim_nl;

    if (pipe(fd_here_doc))
        return (-1);
    lim_nl = ft_strjoin(limiter, "\n");
    if (!lim_nl)
    {
        close(fd_here_doc[0]);
        close(fd_here_doc[1]);
		return (-1);
    }
    while (1)
    {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        if (!line || ft_strcmp(line, lim_nl) == 0)
		{
			free(line);
			break ;
		}
		write(fd_here_doc[1], line, ft_strlen(line));
		free(line);
	}
	free(lim_nl);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

void    close_fds(t_pipex *pipex)
{
    if (pipex->fd_prev > 2)
        close(pipex->fd_prev);
    if (pipex->fd_out > 2)
        close (pipex->fd_out);
    if (pipex->fd[0] > 2)
        close(pipex->fd[0]);
    if (pipex->fd[1] > 2)
        close(pipex->fd[1]);
}
void    free_pipex(t_pipex *pipex)
{
    if (pipex->cmd_tab)
        ft_free_str_tab(pipex->cmd_tab);
    if (pipex->cmd_path)
        free(pipex->cmd_path);
    if (pipex->cmd_path2)
        free(pipex->cmd_path2);
}

void    error_struct(t_pipex *pipex, char *error, int exit_code)
{
    perror(error);
    close_fds(pipex);
    free_pipex(pipex);
    exit(exit_code);
}

void    struct_init(char **av, int ac, t_pipex *pipex, char **envp)
{
    pipex->av = av;
    pipex->envp = envp;
    if (ft_strncmp(av[1], "here_doc", 9) == 0)
    {
        pipex->here_doc = 1;
        pipex->nbr_cmd = ac - 1;
        pipex->fd_prev = handle_here_doc(av[2]);
        if (pipex->fd_prev == -1)
            error_struct(pipex, av[1], 1);
        pipex->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        pipex->start_cmd = 3;
    }
    else
    {
        pipex->here_doc = 0;
        pipex->nbr_cmd = ac - 1;
        pipex->start_cmd = 2;
        pipex->fd_prev = open(av[1], O_RDONLY);
        if (pipex->fd_prev < 0)
            perror (av[1]);
        pipex->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pipex->fd_out < 0)
            perror(av[ac - 1]);
    }
}
void    fork_sons_struct(t_pipex *pipex, int index)
{
    if (pipex->fd_out !=-1)
        close(pipex->fd_out);
    if (pipex->fd_prev == -1)
        exit(1);
    if (dup2(pipex->fd_prev, 0) == -1)
        error_struct(pipex, "dup2", 1);
    if (dup2(pipex->fd[1], 1) == -1)
        error_struct(pipex,"dup2", 1);
    close(pipex->fd[0]);
    close(pipex->fd[1]);
    close(pipex->fd_prev);
    pipex->cmd_tab = ft_split(pipex->av[index], ' ');
    if (check_arg(pipex->av[index]) == 1)
        pipex->cmd_path = cmd_with_path(pipex);
    else
	{
		pipex->cmd_path = ft_strdup(pipex->cmd_tab[0]);
		if (!(access(pipex->cmd_path, F_OK | X_OK) == 0))
			error_struct(pipex, "Command path is incorrect", 127);
	}
    if (!pipex->cmd_path)
        error_struct(pipex, "Command not found", 127);
    if (execve(pipex->cmd_path, pipex->cmd_tab, pipex->envp) == -1)
		error_struct(pipex, "Execve", 127);    
}

void    loop_sons_struct(t_pipex *pipex)
{
    int i;

    i = pipex->start_cmd;
    while (i < pipex->nbr_cmd - 1)
    {
        if (pipe(pipex->fd) == -1)
            error_struct(pipex, "Error in Pipe", 1);
        pipex->pid = fork();
        if (pipex->pid == -1)
            error_struct(pipex, "Error in fork", 1);
        if (pipex->pid == 0)
            fork_sons_struct(pipex, i);
        close(pipex->fd[1]);
        if (pipex->fd_prev != -1)
            close(pipex->fd_prev);
        pipex->fd_prev = pipex->fd[0];
        i++;
    }
}
pid_t   last_sons_struct(t_pipex *pipex)
{
    int dev_null;

    dev_null = 0;
    pipex->pid = fork();
    if (pipex->pid == -1)
        error_struct(pipex, "Error in fork", 1);
    if (pipex->pid == 0)
    {
        if (pipex->fd_prev == -1 ||dup2(pipex->fd_prev, 0) == -1)
            error_struct(pipex, "dup2", 1);
        if (pipex->fd_out == -1)
        {
            int dev_null = open("/dev/null", O_WRONLY);
            if (dev_null == -1 || dup2(dev_null, 1) == -1)
                error_struct(pipex, pipex->av[pipex->nbr_cmd], 1);
            close(dev_null);
        }
        else if (dup2(pipex->fd_out, 1) == -1)
            error_struct(pipex, "dup2", 1);
        close(pipex->fd_prev);
        close(pipex->fd_out);
        pipex->cmd_tab = ft_split(pipex->av[pipex->nbr_cmd - 1], ' ');
        if (check_arg(pipex->av[pipex->nbr_cmd - 1]) == 1)
			pipex->cmd_path = cmd_with_path(pipex);
		else
		{
			pipex->cmd_path = ft_strdup(pipex->cmd_tab[0]);
			if (!(access(pipex->cmd_path, F_OK | X_OK) == 0))
				error_struct(pipex, "Command path is incorrect", 127);
		}
        if (!pipex->cmd_path)
            error_struct(pipex, "Command not found", 127);
		if (execve(pipex->cmd_path, pipex->cmd_tab, pipex->envp) == -1)
			error_struct(pipex, "Exceve", 127);
    }
	return (pipex->pid);
}

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;

    if (ac < 5)
        return (0);
    ft_memset(&pipex, 0, sizeof(t_pipex));
    struct_init(av, ac, &pipex, envp);
    loop_sons_struct(&pipex);
    pipex.last_pid = last_sons_struct(&pipex);
    if (pipex.fd_prev != -1)
		close(pipex.fd_prev);
    if (pipex.fd_out != -1)
	    close (pipex.fd_out);
	waitpid(pipex.last_pid, &pipex.status, 0);
	while (wait(NULL) > 0)
		;
    if (pipex.fd_out == -1)
        pipex.exit_code = 1;  // Erreur d'ouverture du fichier de sortie
    else if (WIFEXITED(pipex.status))
        pipex.exit_code = WEXITSTATUS(pipex.status);
    else
        pipex.exit_code = 0;
    
    return (pipex.exit_code);
}
