#include "minishell.h"

static void	execute_cmd(t_shell *shell, t_cmd *cmd, int i);
static void	wait_all_children(t_shell *shell);

void	execution(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	cmd = shell->cmd;
	shell->num_pipes_fd = setup_pipes(shell, shell->num_pipes);
	i = 0;
    process_heredocs(shell);
	while (cmd)
	{
		setup_redirections_with_pipe(cmd, shell->num_pipes_fd, i, shell->num_pipes);
		execute_cmd(shell, cmd, i);
		if (cmd->next)
			close(shell->num_pipes_fd[i][1]);
		cmd = cmd->next;
		i++;
	}
	wait_all_children(shell);
}

static void	execute_cmd(t_shell *shell, t_cmd *cmd, int i)
{
	pid_t	pid;

	if (is_builtin(cmd->args->value) && shell->num_pipes == 0)
	{
		shell->exit_flag = execute_builtin(shell, cmd);
	}
    else
    {
        pid = fork();
        if (pid < 0)
            shut_program(shell, "Fork failed on execute_cmd()", EXIT_FAILURE);
        else if (pid == 0)
            child_process(shell, cmd, shell->num_pipes_fd, i);
    }
}

static void	wait_all_children(t_shell *shell)
{
	int	status;
	int	last_exit;

	last_exit = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_exit = 128 + WTERMSIG(status);
	}
	shell->exit_flag = last_exit;
}
