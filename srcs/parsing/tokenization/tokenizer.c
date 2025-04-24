#include "minishell.h"
#include "../libft/libft.h"

static char	*get_quote_part(t_shell *shell, char *input, int *i, char **combined);
static char	*get_default_part(t_shell *shell, char *input, int *i, char **combined);
static void	get_combined_token(t_shell *shell, char *input, int *i, t_token **tokens);
static void	get_special_token(t_shell *shell, t_token **tokens, char *input, int *i);

t_token	*tokenizer(t_shell *shell, char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (input[i] == '\0')
			break ;
        if (is_operator(input[i]))
            get_special_token(shell, &tokens, input, &i);
        else
			get_combined_token(shell, input, &i, &tokens);
	}
    update_token_type(tokens);
    print_tokens(shell->token); // ! Will be removed later
	return (tokens);
}

static void	get_combined_token(t_shell *shell, char *input, int *i, t_token **tokens)
{
	char	*combined;
	char	*part;

	combined = ft_strdup("");
	if (!combined)
        shut_program(shell, "Memory allocation failed in get_combined_token()", 1);
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (is_quote(input[*i]))
			part = get_quote_part(shell, input, i, &combined);
		else
			part = get_default_part(shell, input, i, &combined);
		combined = ultimate_join(combined, part);
		if (!combined)
            shut_program(shell, "Memory allocation failed in get_combined_token()", 1);
	}
	add_token(shell, tokens, combined);
	free(combined);
}

static char	*get_quote_part(t_shell *shell, char *input, int *i, char **combined)
{
	int		start;
	char	*new_part;
	char	quote;

	quote = input[(*i)++];
	start = (*i) - 1;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		new_part = ft_substr(input, start, *i - start);
		if (!new_part)
		{
			free(*combined);
			shut_program(shell, "Memory allocation failed in get_quote_part()", 1);
		}
		return (new_part);
	}
    new_part = ft_substr(input, start, ++(*i) - start);
	if (!new_part)
	{
		free(*combined);
        shut_program(shell, "Memory allocation failed in get_quote_part()", 1);
	}
	return (new_part);
}

static char	*get_default_part(t_shell *shell, char *input, int *i, char **combined)
{
	int		start;
	char	*new_part;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
    {
		(*i)++;
    }
	new_part = ft_substr(input, start, *i - start);
	if (!new_part)
	{
		free(*combined);
		shut_program(shell, "Memory allocation failed in get_default_part()", 1);
	}
	return (new_part);
}

static void	get_special_token(t_shell *shell, t_token **tokens, char *input, int *i)
{
	char	operator[3];

	ft_bzero(operator, 3);
	operator[0] = input[*i];
	if (((input[*i] == '|' || input[*i] == '&' || input[*i] == '<' || input[*i] == '>')
		&& input[*i + 1] == input[*i]))
	{
		operator[1] = input[*i + 1];
		(*i) += 2;
	}
	else
		(*i)++;
	add_token(shell, tokens, operator);
}




