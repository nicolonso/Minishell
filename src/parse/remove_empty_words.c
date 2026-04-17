
#include "../../include/minishell.h"

static int	is_empty_str(const char *s)
{
	if (!s)
		return (1);
	return (s[0] == '\0');
}

static void	remove_one(t_token **head, t_token *prev, t_token *cur)
{
	t_token	*next;

	next = cur->next;
	if (prev)
		prev->next = next;
	else
		*head = next;
	free(cur->value);
	free(cur);
}

void	remove_empty_words(t_token **head)
{
	t_token	*cur;
	t_token	*prev;

	if (!head)
		return ;
	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (cur->type == TOK_WORD && is_empty_str(cur->value))
		{
			remove_one(head, prev, cur);
			cur = (prev != NULL) ? prev->next : *head;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

