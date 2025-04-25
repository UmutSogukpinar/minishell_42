#include "minishell.h"
#include "stdlib.h"

void	init_env(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_node;

	if (!shell || !envp)
		return ;
	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(shell, envp[i]);
		add_env_node(&shell->env, new_node);
		i++;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*curr;
	t_env	*next;

	curr = env;
	while (curr)
	{
		next = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
}
