#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define INPUT_RDRCT 60
# define OUTPUT_RDRCT 62
# define PIPE 124

// TODO: fix why this is not recognised in signal.c
// # define _XOPEN_SOURCE 700
// # define _POSIX_C_SOURCE 200809L

// TODO: find necessasary exit codes for proper exit
# define ALLOC_ERR 12 // not enough memory

typedef enum e_bool
{
	C_TRUE = 1,
	C_FALSE = 0

}						t_bool;

// * Token types for lexing
typedef enum e_token_type
{
	TK_WORD,    // Command or argument
	TK_PIPE,    // '|'
	TK_RED_IN,  // '<'
	TK_RED_OUT, // '>'
	TK_APPEND,  // '>>'
	TK_HEREDOC, // '<<'
	TK_ENV_VAR, // '$VAR'
	TK_EOF      // End of file/input
}						t_token_type;

typedef struct s_heredoc
{
	char 			*limiter;
	char			*file_name;
	struct s_heredoc	*next;
}		t_heredoc;

// * Struct for tokens (Lexing)
typedef struct s_token
{
	t_token_type type; // Type of token
	char *value;       // Token value (e.g., "ls", "-l", "|")
	struct s_token		*next;
}						t_token;

// * Command structure
//!  Probably will be changed
typedef struct s_command
{
	char **argv;    // Command arguments ["ls", "-l", NULL] etc.
	char *path;     // Command path
	char *in_file;  // "< file"
	char *out_file; // "> file" or ">> file"
	int					fd_in;
	int					fd_out;
	t_bool append; // Append mode for ">>"
	t_bool				is_builtin;
	struct s_command	*next;
}						t_command;

// * Environment variable storage (for export)
typedef struct s_env
{
	char *key;          // Environment variable name
	char *value;        // Environment variable value
	struct s_env *next; // Next variable
}						t_env;

// * Shell state structure (Global shell context)
typedef struct s_shell
{
	char		*input;
	char		*history;
	t_token 	*token_list;   // Linked list of tokens
	t_heredoc	*heredoc_list;
	t_command	*cmd_list;   // Linked list of commands
	t_env 		*env_list;       // Linked list of environment variables
	char 		**envp;           // Copy of environment variables
	t_bool 		is_interactive; // Whether shell is running interactively
	int			num_heredoc;
}						t_shell;

// ! FUNCTION PROTOTYPES

// * freeing memory
// free_all(t_shell *shell)

// * shutting program
void	shut_program_err(t_shell *shell);

// * Lexing
void	process_input(t_shell *shell);

// * Execution

// * Builtins

// * Environment

// * Signals
void	setup_signals(void);

// * Parse Utils
t_bool	is_operator(char c);
t_bool	is_quote(char c);
char 	*ultimate_join(t_shell *shell, char *s1, char *s2);


// * Tokenization // Token List
void	cr_add_token(t_shell *shell, t_token **h, char *v,
							t_token_type type);

// * Heredoc List
int     heredoc_list_len(t_heredoc *head);
void	cr_add_heredoc(t_shell *shell, t_heredoc **h, char *limiter);


char	*token_default(t_shell *shell, char *input, int *i, char *token);
void	token_operator(t_shell *shell, char *input, int *i);
char 	*token_quote(t_shell *shell, char *input, int *i, char *token);

char 	*concat_default(t_shell *shell, char *input, int *i, char *token);
char 	*concat_quote(t_shell *shell, char *input, int *i, char *token);

// * Interactive Mode
t_bool 	is_interactive(t_shell *shell);
t_bool	ends_with_pipe(t_shell *shell);
void	handle_interactive(t_shell *shell);
t_bool	is_quote_open(t_shell *shell);
int		count_heredoc(t_shell *shell);
t_bool	does_any_heredoc_remain(t_shell *shell);


// * Utils

#endif
