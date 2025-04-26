#include "minishell.h"

static void	resolve_cmd_and_args(t_shell *shell, t_cmd *cmd, char **path, char ***args);

void	child_process(t_shell *shell, t_cmd *cmd, int i)
{
	char	*path;
	char	**args;

	setup_child(cmd, shell, i);
	resolve_cmd_and_args(shell, cmd, &path, &args);
	execve(path, args, shell->og_env); // ? Does this need if condition?
	shut_program(shell, "execve failed", 127);
}


static void	resolve_cmd_and_args(t_shell *shell, t_cmd *cmd, char **path, char ***args)
{
	*path = get_cmd_path(shell, cmd->args->value, &(shell->exit_flag));
	if (!(*path))
	{
		shut_program(shell, NULL, 1);
	}
	*args = modify_args(cmd);
	if (!*args)
	{
		free(*path);
		shut_program(shell, "Failed to modify args", 1);
	}
}

void	close_unused_pipes(t_shell *shell, int current)
{
	int	i;

	i = 0;
	while (i < shell->num_pipes)
	{
		if (i != current)
			close(shell->num_pipes_fd[i][1]);
		if (i != current - 1)
			close(shell->num_pipes_fd[i][0]);
		i++;
	}
}

