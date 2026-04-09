#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_toktype
{
	TOK_WORD = 0,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC
}	t_toktype;

typedef struct s_token
{
	t_toktype	type;
	char	*text;
	struct s_token	*next;
} t_token;

t_token	*tok_new(t_toktype type, char *text);
void	tok_add_back(t_token **lst, t_token *node);
void	tok_free_all(t_token *lst);\

#endif
