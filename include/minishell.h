/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 23:27:21 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/20 12:24:42 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Lib/hdr/libft.h"

/* ── structs ──────────────────────────────────────── */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**av;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env			*env;
	char			**env_arr;
	int				exit_status;
}	t_shell;

/* ── token types ─────────────────────────────────── */
# define TOK_WORD       0
# define TOK_PIPE       1
# define TOK_REDIR_IN   2
# define TOK_REDIR_OUT  3
# define TOK_APPEND     4
# define TOK_HEREDOC    5

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* ── redir type constants ─────────────────────────── */
# define REDIR_IN      1
# define REDIR_OUT     2
# define REDIR_APPEND  3
# define HEREDOC       4

/* ── libft ────────────────────────────────────────── */
void	ft_free_split(char **arr);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(char *s1, const char *s2);
int		is_empty_str(const char *s);

/* ── env build ─────────────────────────────────── */
t_env	*build_env(char **envp);
void	free_env(t_env *env);

/* ── signals ─────────────────────────────────────── */
extern volatile sig_atomic_t	g_sig;

void	setup_signals_prompt(void);
void	setup_signals_exec(void);
void	setup_signals_child(void);

/* ── tokenizer ───────────────────────────────────── */
t_token	*tokenize(const char *input);
void	free_tokens(t_token *tok);
void	remove_empty_words(t_token **head);
t_token	*append_redir(t_token *tok, t_cmd *cmd, int redir_type);
int		redir_type_from_token(int tok_type);
int		is_redir_token(int type);
void	token_append(t_token **head, t_token *new);
t_token	*new_token(int type, char *value);

/* ── parse ────────────────────────────────────────── */

void	free_cmd(t_cmd *cmd);
int		parse_tokenize_error(char *str, t_shell *shell);
int		parse_validate_error(t_shell *shell);
int		parse_redir_error(t_shell *shell);
int		validate_tokens(t_token *tok);
int		prompt_loop(t_shell *shell);
t_cmd	*parse_build_cmds(t_token *tokens, t_shell *shell);
t_cmd	*parse_input(char *str, t_shell *shell);

/* ── expander ─────────────────────────────────────── */
int		expand_tokens(t_token *tok, t_shell *shell);
void	remove_quotes_tokens(t_token *tok);
char	*ms_expand_word(const char *s, t_shell *shell);

/* ── env helpers ──────────────────────────────────── */
void	update_env_value(t_env *env, char *key, char *value);
char	*get_env_value(t_env *env, char *key);
char	**env_to_arr(t_env *env);

/* ── builtins ─────────────────────────────────────── */
int		ft_built_cd(char **av, t_shell *shell);
int		ft_built_echo(char **av, t_shell *shell);
int		ft_built_pwd(char **av, t_shell *shell);
int		ft_built_export(char **av, t_shell *shell);
int		ft_built_unset(char **av, t_shell *shell);
int		ft_built_env(char **av, t_shell *shell);
int		ft_built_exit(char **av, t_shell *shell);

/* ── executor ─────────────────────────────────────── */
char	*get_command_path(char *cmd, t_shell *shell);
int		is_builtin(char *cmd_name);
int		execute_built_in_parent(t_cmd *cmd, t_shell *shell);
int		ft_executor(t_cmd *cmd, t_shell *shell);

/* ── pipeline & redirections ─────────────────────── */
void	child_pipe_setup(int (*pipes)[2], int i, int cmd_count);
void	close_all_pipes(int (*pipes)[2], int count);
int		apply_redirections(t_redir *redir);
int		execute_pipeline(t_cmd *cmd, t_shell *shell);
int		execute_builtin_with_redir(t_cmd *cmd, t_shell *shell);
int		count_cmds(t_cmd *cmd);
int		create_pipes(int (*pipes)[2], int count);
void	exec_path_error(char *path, int code, char *msg);
void	check_direct_path_or_exit(char *path);
void	restore_stdio(int saved_in, int saved_out);

#endif
