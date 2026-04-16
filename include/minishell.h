#ifndef MINISHELL_H
# define MINISHELL_H

/* ── system includes ──────────────────────────────── */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>


/* ── structs ──────────────────────────────────────── */
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_redir
{
    int             type;        /* REDIR_IN, REDIR_OUT, REDIR_APPEND, HEREDOC */
    char            *file;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **av;
    t_redir         *redirs;
    struct s_cmd     *next;       /* for pipes */
}   t_cmd;

typedef struct s_shell
{
    t_env           *env;
    char            **env_arr;   /* char** version for execve */
    int             exit_status;
}   t_shell;

/* ── token types ─────────────────────────────────── */
# define TOK_WORD       0
# define TOK_PIPE       1
# define TOK_REDIR_IN   2
# define TOK_REDIR_OUT  3
# define TOK_APPEND     4
# define TOK_HEREDOC    5

typedef struct s_token
{
    int             type;
    char            *value;
    struct s_token  *next;
}   t_token;

/* ── redir type constants ─────────────────────────── */
# define REDIR_IN      1
# define REDIR_OUT     2
# define REDIR_APPEND  3
# define HEREDOC       4

/* ── libft ────────────────────────────────────────── */
# include "libft.h"

/* ── tokenizer ───────────────────────────────────── */
t_token *tokenize(const char *input);
void    free_tokens(t_token *tok);

/* ── parse ────────────────────────────────────────── */
void    prompt_loop(t_shell *shell);
t_cmd   *parse_input(char *str, t_shell *shell);

/* ── env helpers ──────────────────────────────────── */
char    *get_env_value(t_env *env, char *key);
void    update_env_value(t_env *env, char *key, char *value);
char    **env_to_arr(t_env *env);

/* ── builtins ─────────────────────────────────────── */
int     ft_built_cd(char **av, t_shell *shell);
int     ft_built_echo(char **av, t_shell *shell);
int     ft_built_pwd(char **av, t_shell *shell);
int     ft_built_export(char **av, t_shell *shell);
int     ft_built_unset(char **av, t_shell *shell);
int     ft_built_env(char **av, t_shell *shell);
int     ft_built_exit(char **av, t_shell *shell);

/* ── executor ─────────────────────────────────────── */
int     is_builtin(char *cmd_name);
int     execute_built_in_parent(t_cmd *cmd, t_shell *shell);
int     execute_external(t_cmd *cmd, t_shell *shell);
int     ft_executor(t_cmd *cmd, t_shell *shell);
char    *get_command_path(char *cmd, t_shell *shell);

/* ── pipeline & redirections ─────────────────────── */
int     execute_pipeline(t_cmd *cmd, t_shell *shell);
int     execute_builtin_with_redir(t_cmd *cmd, t_shell *shell);
void    apply_redirections(t_redir *redir);

#endif
