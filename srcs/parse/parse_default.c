
#include "minishell.h"

// purpose: return the length of tokenized value

int	determine_len(char *input, int *i)
{
	int	len;

	len = *i;
	while (input[len] != SPACE && input[len] != DOUBLE_QUOTE
		&& input[len] != SINGLE_QUOTE && input[len] != 0)
	{
		len++;
	}
	return (len - (*i) + 1);
}

void	handle_default(t_shell *shell, char *input, int *i)
{
	char	*value;
	int		index;
	int		len;

	index = 0;
	len = determine_len(input, i);
	value = ft_calloc(len + 1, sizeof(char));
		if (!value)
			return ;  // handle error management
	while (index < len)
	{
		value[index] = input[*i];
		index++;
		(*i)++;
	}
	value[index] = '\0';
}
