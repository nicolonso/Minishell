#include "../../include/minishell.h"
/*
int	parse_tokenize_error(char *str, t_shell *shell)
{
	int	q;

	q = unclosed_quote(str);
	if (q)
		fprintf(stderr,
			"minishell: syntax error: unexpected EOF while looking for matching '%c'\n",
			q);
	else
		fprintf(stderr, "minishell: syntax error\n");
	shell->exit_status = 2;
	return (1);
}

int	parse_validate_error(t_shell *shell)
{
	fprintf(stderr, "minishell: syntax error\n");
	shell->exit_status = 2;
	return (1);
}

t_cmd	*parse_build_cmds(t_token *tokens)
{
	t_token	*cur;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new;

	cur = tokens;
	head = NULL;
	tail = NULL;
	while (cur)
	{
		new = build_cmd(&cur);
		if (!new)
			break ;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
	}
	return (head);
}*/
