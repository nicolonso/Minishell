#include "../../include/minishell.h"

static int	is_redir_token(int type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC);
}

int	validate_tokens(t_token *tok)
{
	t_token	*prev;

	if (!tok)
		return (0);

	if (tok->type == TOK_PIPE)
		return (-1);

	prev = NULL;
	while (tok)
	{
		if (tok->type == TOK_PIPE && tok->next && tok->next->type == TOK_PIPE)
			return (-1);

		if (is_redir_token(tok->type))
		{
			if (!tok->next || tok->next->type != TOK_WORD)
				return (-1);
		}

		prev = tok;
		tok = tok->next;
	}

	if (prev && prev->type == TOK_PIPE)
		return (-1);

	return (0);
}
