#include "minishell.h"
#include "../libft/libft.h"

static void set_infile(t_cmd *cmd, char *file);
static void set_outfile(t_cmd *cmd, char *file, bool is_append, bool is_trunc);
static void set_heredoc(t_cmd *cmd, char *file);
static char    *get_filename(t_shell *shell);

void    parse_redirection(t_shell *shell, t_cmd *cmd)
{
    t_token *token;
    char    *file;
    bool    is_append;

    token = shell->token;
    is_append = (token->type == APPEND);
    advance_token(shell);
    file = get_filename(shell);
    if (token->type == HEREDOC)
        set_heredoc(cmd, file);
    else if (token->type == REDIRECT_IN)
        set_infile(cmd, file);
    else
        set_outfile(cmd, file, is_append, token->type == REDIRECT_OUT);
}

static char    *get_filename(t_shell *shell)
{
    char    *file;

    if (!shell->token || shell->token->type != WORD)
    {
        ft_putendl_fd("minishell: Expected filename after redir", STDERR_FILENO);
        shut_program(shell, "Invalid redirection", EX_KO);
    }
    file = ft_strdup(shell->token->value);
    if (!file)
        shut_program(shell, "Allocation failed for filename", EX_KO);
    advance_token(shell);
    return (file);
}


static void set_infile(t_cmd *cmd, char *file)
{
    if (cmd->infile)
        free(cmd->infile);
    cmd->infile = file;
}

static void set_outfile(t_cmd *cmd, char *file, bool is_append, bool is_trunc)
{
    if (cmd->outfile)
        free(cmd->outfile);
    cmd->outfile = file;
    cmd->has_append = is_append;
    cmd->has_trunc = is_trunc;
    if(cmd->has_trunc)
        cmd->has_append = false;
}

static void set_heredoc(t_cmd *cmd, char *file)
{
    if (cmd->has_heredoc && cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    cmd->has_heredoc = true;
    cmd->heredoc_delim = file;
}
