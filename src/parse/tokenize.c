/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 00:00:00 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/03/27 00:00:00 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tok_new(t_toktype type, char *text)
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
	char	**words;
	t_token	*head;
	t_token	*node;
	int		i;

	head = NULL;
	words = split(input);
	if (!words)
		return (NULL);
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

