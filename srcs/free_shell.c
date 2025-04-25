#include "minishell.h"
#include "../libft/libft.h"

void	shut_program(t_shell *shell, char *msg, int exit_code)
{
    if (msg)
        ft_putendl_fd(msg, STDERR_FILENO);
    if (!shell)
        return ;
    exit(exit_code);
}

void    free_shell(t_shell *shell)
{
    if (!shell)
        return ;
    clear_history();
    if (shell->input)
        free(shell->input);
    free_tokens(shell->token);
    free_cmd_list(shell->cmd);
    free_env_list(shell->env);
    free(shell);
}


