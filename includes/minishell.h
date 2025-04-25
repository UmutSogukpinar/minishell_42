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


#define HEREDOC_PIPE_ERROR 1
#define HEREDOC_FORK_ERROR 2
#define HEREDOC_EXIT_OK 0
#define HEREDOC_EXIT_INTERRUPTED 130

# define PROMPT "minishell> "
# define HEREDOC_PROMPT "heredoc> "

# define PIPE_PAIR 2


extern volatile sig_atomic_t	g_signal;


// * =======================================================>>>>> Shuting down

void	shut_program(t_shell *shell, char *msg, int exit_code);
void    free_shell(t_shell *shell);

void	free_str_array(char **arr);


// * =======================================================>>>>> String utils

void skip_spaces(char *input, int *i);
bool ft_isspace(char c);
bool	is_quote(char c);
char	*ultimate_join(char *s1, char *s2);
bool	are_strs_equal(char *s1, char *s2);

// * =======================================================>>>>> Token utils

void	print_tokens(t_token *tokens); // ! Will be removed later
bool    is_operator(char c);
void	update_token_type(t_token *tokens);
bool	is_operator_type(t_token_type type);
bool	is_redirection_type(t_token_type type);

void    free_tokens(t_token *tokens);
void	add_token(t_shell *shell, t_token **tokens, char *value);
void	advance_token(t_shell *shell);

t_token	*tokenizer(t_shell *shell, char *input);

// * =======================================================>>>>> Syntax checker
bool	check_syntax(t_token *tokens);
bool	are_quotes_closed(t_token *tokens);


// * =======================================================>>>>> Parser utils

t_cmd *parser(t_shell *shell);
void	parse_redirection(t_shell *shell, t_cmd *cmd);

t_cmd	*new_cmd_node(t_shell *shell);
void	free_cmd_list(t_cmd *head);
void	print_cmd_list(t_cmd *head); // ! Will be removed later

t_dir *create_redir_node(t_shell *shell, t_redir_type type, char *filename);
void add_redir_node(t_dir **redir_list, t_dir *new_node);


// * =======================================================>>>>> Environment utils

void	init_env(t_shell *shell, char **envp);
void	free_env_list(t_env *env);
t_env	*create_env_node(t_shell *shell, char *env_var);
void	add_env_node(t_env **env_list, t_env *new_node);
char    *get_env_value(t_env *env, char *key);
void	print_env_list(t_env *env); // ! Will be removed later

// * =======================================================>>>>> Execution utils

bool process_heredocs(t_shell *shell);

int     **setup_pipes(t_shell *shell, int num_pipes);
void    free_pipe_fd(int **pipe_fd, int num);
int     count_pipes(t_cmd *cmd);
void	setup_redirections_with_pipe(t_cmd *cmd, int **pipe_fd, int i, int num_pipes);


// * =======================================================>>>>> Builtin utils

bool	is_builtin(char *cmd);
int     execute_builtin(t_shell *shell, t_cmd *cmd);

int	        ft_cd(char **args, t_env *env);
int     	ft_echo(char **args);
int     	ft_env(t_shell *shell);
int     	ft_exit(char **args);
int			ft_export(t_shell *shell, char **args);
int     	ft_pwd(void);
int     	ft_unset(t_shell *shell, char **args);


// * =======================================================>>>>> Path utils

void	path_error_msg(char *cmd, int exit_code, bool is_direct);
char	*get_path(t_shell *shell, char *cmd, int *exit_code);

#endif
