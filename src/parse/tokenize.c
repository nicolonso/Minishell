
#include "../../include/minishell.h"
/*
static t_toktype	op_type(const char *s, size_t i)
{
	if (s[i] == '|')
		return (TOK_PIPE);
	if (s[i] == '>' && s[i + 1] == '>')
		return (TOK_APPEND);
	if (s[i] == '<' && s[i + 1] == '<')
		return (TOK_HEREDOC);
	if (s[i] == '>')
		return (TOK_REDIR_OUT);
	return (TOK_REDIR_IN);
}*/

t_token *tok_new(t_toktype type, char *text)
{
t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->text = text;
	node->next = NULL;
	return (node);
}

void	tok_add_back(t_token **lst, t_token *node)
{
	t_token	*cur;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

void	tok_free_all(t_token *lst)
{
	t_token	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->text);
		free(lst);
		lst = next;
	}
}

t_token	*tokenize(char *input)
{
	char **words;
	t_token *head;
	t_token *node;
	int	i;

	if (!input || !*input)
		return (NULL);
	head = NULL;
	words = split(input);
	if (!words)
		return NULL;
	i = 0;
	while (words[i])
	{
		node = tok_new(TOK_WORD, words[i]);
		if (!node)
		{
			while (words[i])
				free(words[i++]);
			free(words);
			tok_free_all(head);
			return (NULL);
		}
		tok_add_back(&head, node);
		i++;
	}
	free(words);
	return (head);
}

void	print_tokens(t_token *toks)
{
	int	i;

	i = 0;
	while (toks)
	{
		printf("tok%i: %s\n", i, toks->text);
		toks = toks->next;
		i++;
	}
}
