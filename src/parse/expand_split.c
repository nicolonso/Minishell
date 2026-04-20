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

static int	has_quotes(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	is_sep(char c)
{
	return (c == ' ' || c == '\t');
}

static char	*next_field(char *s, int *i)
{
	int		start;
	int		len;

	while (s[*i] && is_sep(s[*i]))
		(*i)++;
	start = *i;
	while (s[*i] && !is_sep(s[*i]))
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (NULL);
	return (ft_strndup(s + start, len));
}

static void	insert_fields(t_token **head, t_token *prev, t_token *cur)
{
	int		i;
	char	*field;
	t_token	*new;
	t_token	*last;

	i = 0;
	last = prev;
	while (1)
	{
		field = next_field(cur->value, &i);
		if (!field)
			break ;
		new = new_token(TOK_WORD, field);
		if (!new)
			break ;
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
}

void	split_expanded_tokens(t_token **tok)
{
	t_token	*prev;
	t_token	*cur;

	prev = NULL;
	cur = *tok;
	while (cur)
	{
		if (cur->type == TOK_WORD && cur->value)
		{
			if (!has_quotes(cur->value) && ft_strchr(cur->value, ' '))
			{
				insert_fields(tok, prev, cur);
				if (prev)
					cur = prev->next;
				else
					cur = *tok;
				continue ;
			}
		}
		prev = cur;
		cur = cur->next;
	}
}
