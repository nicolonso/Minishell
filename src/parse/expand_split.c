/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:23:46 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/20 15:23:48 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_internal.h"

static int	ms_is_sep(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static char	*ms_next_field(char *s, int *i)
{
	int	start;

	while (s[*i] && ms_is_sep(s[*i]))
		(*i)++;
	start = *i;
	while (s[*i] && !ms_is_sep(s[*i]))
		(*i)++;
	if (*i <= start)
		return (NULL);
	return (ft_strndup(s + start, *i - start));
}

static int	ms_split_insert(t_token **head, t_token *prev, t_token *cur)
{
	int		i;
	char	*field;
	t_token	*new;
	t_token	*last;

	i = 0;
	last = prev;
	while (1)
	{
		field = ms_next_field(cur->value, &i);
		if (!field)
			break ;
		new = new_token(TOK_WORD, field);
		if (!new)
			return (free(field), 1);
		if (!last)
			*head = new;
		else
			last->next = new;
		last = new;
	}
	if (last)
		last->next = cur->next;
	free(cur->value);
	free(cur);
	return (0);
}

int	split_expanded_tokens(t_token **tok)
{
	t_token	*prev;
	t_token	*cur;

	prev = NULL;
	cur = *tok;
	while (cur)
	{
		if (ms_token_needs_split(cur))
		{
			if (ms_split_insert(tok, prev, cur) != 0)
				return (1);
			if (prev)
				cur = prev->next;
			else
				cur = *tok;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
