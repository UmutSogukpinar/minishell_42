#include "minishell.h"

static int	setup_heredoc(t_shell *shell, t_cmd *cmd);
static void	handle_heredoc_child(t_cmd *cmd);
static int	wait_for_child(pid_t pid);

bool process_heredocs(t_shell *shell)
{
    t_cmd *cmd;

    cmd = shell->cmd;
    while (cmd)
    {
        if (cmd->has_heredoc && cmd->heredoc_delim)
        {
            if (!setup_heredoc(shell, cmd))
            {
                // If heredoc is interrupted, return false to exit early
                return (false);
            }
        }
        cmd = cmd->next;
    }
    return (true);
}

static int	setup_heredoc(t_shell *shell, t_cmd *cmd)
{
	if (pipe(cmd->heredoc_fd) == -1)
	{
		shut_program(shell, "Pipe error in setup_heredoc()", EXIT_FAILURE);
		return (HEREDOC_PIPE_ERROR);
	}
	pid_t pid = fork();
	if (pid < 0)
	{
		shut_program(shell, "Fork error in setup_heredoc()", HEREDOC_FORK_ERROR);
		return (HEREDOC_FORK_ERROR);
	}
	else if (pid == 0)
		handle_heredoc_child(cmd);

	close(cmd->heredoc_fd[1]);
	cmd->in_fd = cmd->heredoc_fd[0];
	return (wait_for_child(pid));
}

static void	handle_heredoc_child(t_cmd *cmd)
{
    char *line;

    // TODO: Handle signals for heredoc child process

    while (1)
    {
        line = readline(HEREDOC_PROMPT);
        if (!line)
        {
            ft_putendl_fd("\nEnd of input (Ctrl+D)", STDERR_FILENO); // ? Does this need to be customized?
            break ;
        }
        if (are_strs_equal(line, cmd->heredoc_delim))
        {
            free(line);
            break ;
        }
        ft_putendl_fd(line, cmd->heredoc_fd[1]);
        free(line);
    }
    close(cmd->heredoc_fd[1]);
    if (!line)
        exit(EX_OK);
    exit(HEREDOC_EXIT_INTERRUPTED); // ? Is this the right exit code and should it be used?
}

static int	wait_for_child(pid_t pid)
{
	int	status;
    int signal_num;
    int exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			return (exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		return (128 + signal_num);
	}
	return (HEREDOC_EXIT_OK);
}
