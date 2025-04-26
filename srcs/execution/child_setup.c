#include "minishell.h"

static bool	has_output_redirection_via_list(t_cmd *cmd);
static bool	has_input_redirection_via_list(t_cmd *cmd);

void	setup_child(t_cmd *cmd, t_shell *shell, int i)
{
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
		if (has_input_redirection_via_list(cmd) && i > 0)
			close(shell->num_pipes_fd[i - 1][0]);
	}
	if (cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);

		if (has_output_redirection_via_list(cmd) && i < shell->num_pipes)
			close(shell->num_pipes_fd[i][1]);
	}
	close_unused_pipes(shell, i);
}


static bool	has_output_redirection_via_list(t_cmd *cmd)
{

	t_dir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == DIR_OUT || redir->type == DIR_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

static bool	has_input_redirection_via_list(t_cmd *cmd)
{
	t_dir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == DIR_IN || redir->type == DIR_HEREDOC)
			return (true);
		redir = redir->next;
	}
	return (false);
}
