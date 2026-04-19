/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 19:19:30 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/19 19:19:32 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_join_free(char *dst, char *add)
{
	char	*tmp;

	if (!dst || !add)
		return (free(dst), free(add), NULL);
	tmp = ft_strjoin(dst, add);
	free(dst);
	free(add);
	return (tmp);
}

static int	update_state(int state, char c)
{
	if (state == 0 && (c == '\'' || c == '"'))
	{
		if (c == '\'')
			return (1);
		return (2);
	}
	if (state == 1 && c == '\'')
		return (0);
	if (state == 2 && c == '"')
		return (0);
	return (state);
}

static int	is_quote_toggle(int state, char c)
{
	if (state == 0 && (c == '\'' || c == '"'))
		return (1);
	if (state == 1 && c == '\'')
		return (1);
	if (state == 2 && c == '"')
		return (1);
	return (0);
}

static char	*remove_quotes_word(const char *s)
{
	int		i;
	int		state;
	char	*out;
	char	tmp[2];

	i = 0;
	state = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (is_quote_toggle(state, s[i]))
		{
			state = update_state(state, s[i]);
			i++;
			continue ;
		}
		tmp[0] = s[i++];
		tmp[1] = '\0';
		out = str_join_free(out, ft_strdup(tmp));
		if (!out)
			return (NULL);
	}
	return (out);
}

void	remove_quotes_tokens(t_token *tok)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && tok->value)
		{
			newv = remove_quotes_word(tok->value);
			if (newv)
			{
				free(tok->value);
				tok->value = newv;
			}
		}
		tok = tok->next;
	}
}
