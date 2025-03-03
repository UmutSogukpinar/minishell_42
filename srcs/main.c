#include "minishell.h"

//purpose: initialize a main structure for the minishell  //* added by umut
//context: everything initialize as NULL except is_interactive

t_shell	*init_shell(void)
{
	t_shell	*new;

	new = ft_calloc(1, sizeof(t_shell));
	if (!new)
		return (NULL);
	new->is_interactive = C_FALSE;
	return (new);
}

void	shell_loop(t_shell *shell)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		printf("%s\n", input); // ? test
		add_history(input); // ? do we need to use rl_clear_histroy for leaks ?
		process_input(input); // TODO: Implement this function
		free(input); // ? is this necessary
	}
	// TODO:
	// // Display a prompt (minishell$ ).
	// Read user input (Parse & Tokenise).
	// Process and execute the command.
	// // Add the command that is run to history.
	// // Repeat until the user exits.
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = init_shell();
	if (!shell)
		return (ALLOC_ERR);
	setup_signals(); // TODO: Implement this function
	shell_loop(shell);
	return (0);
}
