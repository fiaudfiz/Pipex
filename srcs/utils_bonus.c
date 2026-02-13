#include "pipex.h"
#include "../libft/includes/libft.h"

char	*cmd_with_path_bonus(char **cmd_tab, char **envp)
{
	char	**path;
	char	*cmd_path;

	path = get_path(envp);
	if (!path)
		msg_error_path_bonus("Invalid Path");
	cmd_path = find_cmd_path(path, cmd_tab);
	ft_free_str_tab(path);
	if (!cmd_path || !cmd_tab[0])
	{
		ft_free_str_tab(cmd_tab);
		msg_error_cmd_bonus("Command not found");
		return (NULL);
	}
	return (cmd_path);
}
