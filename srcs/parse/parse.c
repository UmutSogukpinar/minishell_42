#include "minishell.h"

// purpose: update the token_list in "shell" structure

void	tokenise_input(t_shell *shell, char *input)
{
	t_token	*new;
	int		i;

	// TODO:
	// Control "double quote" and "quote"  ---> by using sub-functions
	// Split arguments and return tokenised input.
	// final process
	i = -1;
	while (input[++i])
	{
		if (input[i] == SPACE)
			continue ;
		if (input[i] == DOUBLE_QUOTE)
			handle_double_quote(input, &i);
		else if (input[i] == SINGLE_QUOTE)
			handle_single_quote(input, &i);
		else
			handle_default(shell, input, &i);
	}
}

// ? Example: ["ls", "-l", "|", "grep", "minishell", ">", "output.txt"]

void	process_input(t_shell *shell, char *input)
{
	// TODO:
	// Take input, call tokenise_input
	// Execute command
}
