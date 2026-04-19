#include "minishell.h"

int	is_redir_token(int type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC);
}

int	redir_type_from_token(int tok_type)
{
	if (tok_type == TOK_REDIR_IN)
		return (REDIR_IN);
	if (tok_type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	if (tok_type == TOK_APPEND)
		return (REDIR_APPEND);
	return (HEREDOC);
}

t_token	*append_redir(t_token *tok, t_cmd *cmd, int redir_type)
{
	t_redir	*redir;
	t_redir	*last;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = redir_type;
	redir->file = ft_strdup(tok->value);
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
	return (tok->next);
}