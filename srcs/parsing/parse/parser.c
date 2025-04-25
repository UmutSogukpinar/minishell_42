#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static t_token  *get_segment(t_token **tokens);
static t_token  *collect_args_list(t_shell *shell);

t_cmd   *parser(t_shell *shell)
{
    t_cmd *head;
    t_cmd *tail;

    head = new_cmd_node(shell);
    tail = head;
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

static t_token  *get_segment(t_token **tokens)
{
    t_token *start;
    t_token *end;

    start = *tokens;
    end = start;
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
    t_token *start;
    t_token *end;

    start = NULL;
    end = NULL;
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
