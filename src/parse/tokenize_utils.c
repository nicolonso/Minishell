#include "minishell.h"

t_token	*tok_new(int type, char *value)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

void	tok_append(t_token **head, t_token *new_tok)
{
	t_token	*cur;

	if (!*head)
	{
		*head = new_tok;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_tok;
}

int	read_quoted(const char *s, int i, char *buf, int *len)
{
	char	quote;

	quote = s[i];
	if (*len >= 4095)
		return (-1);
	buf[(*len)++] = s[i++];
	while (s[i] && s[i] != quote)
	{
		if (*len >= 4095)
			return (-1);
		buf[(*len)++] = s[i++];
	}
	if (s[i] != quote)
		return (-1);
	if (*len >= 4095)
		return (-1);
	buf[(*len)++] = s[i++];
	return (i);
}