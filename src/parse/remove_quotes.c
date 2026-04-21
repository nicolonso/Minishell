/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:29:28 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/20 12:31:50 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_char(char **out, char c)
{
	char	tmp[2];
	char	*add;
	char	*newv;

	tmp[0] = c;
	tmp[1] = '\0';
	add = ft_strdup(tmp);
	if (!add)
		return (1);
	newv = ft_strjoin(*out, add);
	free(add);
	if (!newv)
		return (1);
	free(*out);
	*out = newv;
	return (0);
}

static int	handle_quote_state(const char *s, int *i, int *state)
{
	if (*state == 0 && (s[*i] == '\'' || s[*i] == '"'))
	{
		if (s[*i] == '\'')
			*state = 1;
		else
			*state = 2;
		(*i)++;
		return (1);
	}
	if (*state == 1 && s[*i] == '\'')
	{
		*state = 0;
		(*i)++;
		return (1);
	}
	if (*state == 2 && s[*i] == '"')
	{
		*state = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static char	*remove_quotes_word(const char *s)
{
	int		i;
	int		state;
	char	*out;

	i = 0;
	state = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (handle_quote_state(s, &i, &state))
			continue ;
		if (append_char(&out, s[i]))
			return (NULL);
		i++;
	}
	return (out);
}

int	remove_quotes_tokens(t_token *tok)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && tok->value)
		{
			newv = remove_quotes_word(tok->value);
			if (!newv)
				return (1);
			free(tok->value);
			tok->value = newv;
		}
		tok = tok->next;
	}
	return (0);
}
