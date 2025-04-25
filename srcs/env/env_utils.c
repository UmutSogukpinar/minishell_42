#include "minishell.h"
#include "../libft/libft.h"

static void	set_env_key_value(t_shell *shell, t_env *node, char *env_var);

void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!new_node)
		return ;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env	*create_env_node(t_shell *shell, char *env_var)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
    if (!new_node)
    {
        shut_program(shell, "Alloc error on create_env_node()", EX_KO);
    }
	set_env_key_value(shell, new_node, env_var);
	return (new_node);
}

static void	set_env_key_value(t_shell *shell, t_env *node, char *env_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
	{
		node->key = ft_strdup(env_var);
		if (!node->key)
			shut_program(shell, "Alloc error on set_env_key_value()", EX_KO);
		node->value = NULL;
	}
    else
    {
        node->key = ft_substr(env_var, 0, equal_sign - env_var);
        if (!node->key)
            shut_program(shell, "Alloc error on set_env_key_value()", EX_KO);
        node->value = ft_strdup(equal_sign + 1);
        if (!node->value)
        {
            free(node->key);
            shut_program(shell, "Alloc error on set_env_key_value()", EX_KO);
        }
    }
}
