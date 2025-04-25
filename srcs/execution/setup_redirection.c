#include "minishell.h"

static void	handle_redirections(t_cmd *cmd);
static void	handle_in_redir(t_cmd *cmd, t_dir *redir);
static void	handle_out_redir(t_cmd *cmd, t_dir *redir);
static void	handle_heredoc_redir(t_cmd *cmd, t_dir *redir);

void	setup_redirections_with_pipe(t_cmd *cmd, int **pipe_fd, int i, int num_pipes)
{
	handle_redirections(cmd);
    // * If there is no redirection, set the default in_fd and out_fd 
	if (cmd->in_fd == STDIN_FILENO && i > 0)
		cmd->in_fd = pipe_fd[i - 1][0];
	if (cmd->out_fd == STDOUT_FILENO && i < num_pipes)
		cmd->out_fd = pipe_fd[i][1];
}

static void	handle_redirections(t_cmd *cmd)
{
	t_dir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == DIR_IN)
			handle_in_redir(cmd, redir);
		else if (redir->type == DIR_OUT || redir->type == DIR_APPEND)
			handle_out_redir(cmd, redir);
		else if (redir->type == DIR_HEREDOC)
			handle_heredoc_redir(cmd, redir);
		redir = redir->next;
	}
}

static void	handle_in_redir(t_cmd *cmd, t_dir *redir)
{
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	cmd->in_fd = open(redir->filename, O_RDONLY);
}

static void	handle_out_redir(t_cmd *cmd, t_dir *redir)
{
	if (cmd->out_fd != STDOUT_FILENO)
		close(cmd->out_fd);
	if (redir->type == DIR_OUT)
		cmd->out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

static void	handle_heredoc_redir(t_cmd *cmd, t_dir *redir)
{
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	cmd->in_fd = redir->heredoc_fd[0];
}

