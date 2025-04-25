#include "minishell.h"
#include "../libft/libft.h"

t_cmd	*new_cmd_node(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		shut_program(shell, "Alloc error on new_cmd_node()", EX_KO);
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	cmd->has_append = false;
    cmd->has_trunc = false;
	cmd->has_heredoc = false;
	cmd->next = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	return (cmd);
}

void    free_cmd_list(t_cmd *head)
{
    t_cmd *curr;
    t_cmd *next;

    curr = head;
    while (curr)
    {
        next = curr->next;
        if (curr->infile)
            free(curr->infile);
        if (curr->outfile)
            free(curr->outfile);
        if (curr->has_heredoc && curr->heredoc_delim)
            free(curr->heredoc_delim);
        if (curr->args)
            free_tokens(curr->args);
        free(curr);
        curr = next;
    }
}

void            print_cmd_list(t_cmd *head) // ! Will be removed later
{
    t_cmd   *curr = head;
    t_token *arg;

    while (curr)
    {
        printf("Command:\n");
        printf("  args:");
        arg = curr->args;
        if (!arg)
            printf(" (none)");
        while (arg)
        {
            printf(" %s", arg->value);
            arg = arg->next;
        }
        printf("\n");

        if (curr->infile)
            printf("  infile: %s\n", curr->infile);
        else
            printf("  infile: (none)\n");

        if (curr->outfile)
            printf("  outfile: %s\n", curr->outfile);
        else
            printf("  outfile: (none)\n");

        printf("  has_append: %s\n",
            curr->has_append ? "true" : "false");

        printf("  has_heredoc: %s\n",
            curr->has_heredoc ? "true" : "false");

        if (curr->has_heredoc)
            printf("  heredoc_delim: %s\n",
                curr->heredoc_delim);
        else
            printf("  heredoc_delim: (none)\n");

        curr = curr->next;
    }
}

