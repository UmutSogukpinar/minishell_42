#ifndef SH_EXPANSION_H
# define SH_EXPANSION_H

# include "structs.h"

// * =======================================================>>>>> Variable Expansion

void	expand_and_unquote_cmd_list(t_shell *shell);
void	fill_vars(t_shell *shell, char *input, char *expanded, t_buffer *buf);

char	*expand_vars(t_shell *shell, char *input);
char	*remove_quotes_update_str(t_shell *shell, char *str);

// * =======================================================>>>>> Helpers

void	ft_strcpy_to(char *dst, char *src, int *j);

int		measure_len(t_shell *shell, char *input);
int		handle_env_var_len(t_shell *shell, char *str, int *i, bool is_in_q);

#endif
