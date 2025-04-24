#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "structures.h"

# define EX_OK EXIT_SUCCESS
# define EX_KO EXIT_FAILURE
# define INV_ARGC 2

# define PROMPT "minishell> "


extern volatile sig_atomic_t	g_signal;


// * =======================================================>>>>> Shuting and freeing utils

void	shut_program(t_shell *shell, char *msg, int exit_code);
void    free_shell(t_shell *shell);

void    free_tokens(t_token *tokens);


// * =======================================================>>>>> String utils

void skip_spaces(char *input, int *i);
bool ft_isspace(char c);
bool	is_quote(char c);
char	*ultimate_join(char *s1, char *s2);
bool	are_strs_equal(char *s1, char *s2);

// * =======================================================>>>>> Parsing utils

void	print_tokens(t_token *tokens); // ! Will be removed later
bool    is_operator(char c);
void	update_token_type(t_token *tokens);
bool	is_operator_type(t_token_type type);
bool	is_redirection_type(t_token_type type);

void	add_token(t_shell *shell, t_token **tokens, char *value);

bool	check_syntax(t_token *tokens);

t_token	*tokenizer(t_shell *shell, char *input);



#endif
