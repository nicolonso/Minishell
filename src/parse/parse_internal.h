#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H

# include "minishell.h"

/*
** tokenize_utils.c
*/
t_token	*tok_new(int type, char *value);
void	tok_append(t_token **head, t_token *new_tok);
int		read_quoted(const char *s, int i, char *buf, int *len);

/*
** parse_build_utils.c
*/
int		is_redir_token(int type);
int		redir_type_from_token(int tok_type);
t_token	*append_redir(t_token *tok, t_cmd *cmd, int redir_type);

/*
** expand_utils.c
*/
int		is_name_start(char c);
int		is_name_char(char c);
char	*str_join_free(char *dst, char *add);
char	*itoa_status(int st);
char	*dup_key_range(const char *s, int start, int end);

#endif