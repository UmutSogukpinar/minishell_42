#include "minishell.h"
#include "../libft/libft.h"

static void init_shell(t_shell *shell, char **envp);
static void make_ready_for_next_prompt(t_shell *shell);
static void shell_loop(t_shell *shell);

// * Main function
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1) // TODO: Add invalid number of arguments error code (2)
		shut_program(NULL, "Invalid number of arguments", INV_ARGC);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
	{
		ft_putendl_fd("Memory allocation error on main()", STDERR_FILENO);
		return (EX_KO);
	}
	init_shell(shell, envp);
	shell_loop(shell);
	free_shell(shell);
	return (0);
}

static void shell_loop(t_shell *shell)
{
	char *prompt;

	while (1)
	{
        make_ready_for_next_prompt(shell); // ? Is double checking needed?
		prompt = readline(PROMPT);
		if (!prompt)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (prompt[0] != '\0')
			add_history(prompt);
        shell->input = prompt;
		shell->token = tokenizer(shell, prompt);
        if (!check_syntax(shell->token))
            continue;
        make_ready_for_next_prompt(shell);
	}
}

static void make_ready_for_next_prompt(t_shell *shell)
{
    if (shell->input)
        free(shell->input);
    shell->input = NULL;
    free_tokens(shell->token);
    shell->token = NULL;
    // TODO: Update later
}

static void init_shell(t_shell *shell, char **envp) // ? Check if this is needed
{
	shell->input = NULL;
	shell->exit_flag = 0;
	shell->num_pipes = 0;
	shell->og_env = envp;
	shell->env = NULL;
	shell->cmd = NULL;
	shell->token = NULL;
	// g_signal = 0; // ?  Is this supposed to be here?
}
