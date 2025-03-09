#include "minishell.h"

const char *get_token_type_name(t_token_type type);
void display_tokens(t_token *head);

void	shell_loop(t_shell *shell)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)	// * Handles Ctrl + D
		{
			printf("exit\n");
			break ;
		}
		shell->input = ft_strdup(input);
		free(input);
		if (!shell->input)
			shut_program_err(shell);
		shell->history = ft_strdup(shell->input);
		process_input(shell);
	}
	// TODO:
	// // Display a prompt (minishell$ ).
	// // Read user input (Parse & Tokenise).
	// Process and execute the command.
	// // Add the command that is run to history.
	// // Repeat until the user exits.
}

//* purpose: initialization of main structure (t_shell)

t_shell	*init_shell(void)
{
	t_shell	*new;

	new = ft_calloc(1, sizeof(t_shell));
	if (!new)
		return (NULL);
	new->is_interactive = C_FALSE;
	return (new);
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = init_shell();
	if (!shell)
		return (ALLOC_ERR); // ? special message for any error maybe?
	setup_signals();
	shell_loop(shell);
	return (0);
}


void display_tokens(t_token *head)
{
    while (head)
    {
        printf("Type: %-12s | Value: %s\n", 
            get_token_type_name(head->type), 
            (head->value && head->value[0] != '\0') ? head->value : "\"\""
        );
        head = head->next;
    }
}

const char *get_token_type_name(t_token_type type)
{
    switch (type)
    {
    case TK_WORD:
        return "WORD";
    case TK_PIPE:
        return "PIPE";
    case TK_RED_IN:
        return "REDIRECT_IN";
    case TK_RED_OUT:
        return "REDIRECT_OUT";
    case TK_APPEND:
        return "APPEND";
    case TK_HEREDOC:
        return "HEREDOC";
    case TK_ENV_VAR:
        return "ENV_VAR";
    case TK_EOF:
        return "EOF";
    default:
        return "UNKNOWN";
    }
}
