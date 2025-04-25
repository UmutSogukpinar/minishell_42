#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static t_token  *get_segment(t_token **tokens)
{
    t_token *start = *tokens;
    t_token *end = start;

    while (end && end->type != PIPE)
        end = end->next;
    if (!end)
        *tokens = NULL;
    else
    {
        *tokens = end->next;
        end->next = NULL;
    }
    return (start);
}

static t_token  *collect_args_list(t_shell *shell)
{
    t_token *start = NULL;
    t_token *end = NULL;

    while (shell->token && shell->token->type == WORD)
    {
        if (!start)
            start = shell->token;
        end = shell->token;
        shell->token = shell->token->next;
    }
    if (end)
        end->next = NULL;
    return (start);
}

static t_cmd *parse_command(t_shell *shell)
{
    t_cmd *head = new_cmd_node(shell);
    t_cmd *tail = head;

    while (shell->token)
    {
        while (shell->token && is_redirection_type(shell->token->type))
            parse_redirection(shell, tail);

        tail->args = collect_args_list(shell);

        while (shell->token && is_redirection_type(shell->token->type))
            parse_redirection(shell, tail);

        if (shell->token && shell->token->type == PIPE)
        {
            advance_token(shell);
            tail->next = new_cmd_node(shell);
            tail = tail->next;
            continue;
        }
        break;
    }
    return (head);
}


void    parser(t_shell *shell)
{
    shell->cmd = parse_command(shell);
}
