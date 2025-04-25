#include "minishell.h"
#include "../libft/libft.h"

void	shut_program(t_shell *shell, char *msg, int exit_code)
{
    if (msg)
        ft_putendl_fd(msg, STDERR_FILENO);
    if (!shell)
        return ;
    free_shell(shell);
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
    free_pipe_fd(shell->num_pipes_fd, shell->num_pipes);
    free(shell);
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	path_error_msg(char *cmd, int exit_code, bool is_direct)
{
	if (exit_code == 127)
	{
		if (is_direct)
			ft_putstr_fd("minishell: no such file or directory: ", STDERR_FILENO);
		else
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	}
	else if (exit_code == 126)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
	}
	ft_putendl_fd(cmd, STDERR_FILENO);
}

