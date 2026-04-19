/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 19:36:46 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/19 19:36:48 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_internal.h"

static int	update_quote_state(int state, char c)
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

static char	*append_char(char *out, char c)
{
	char	chunk[2];

	chunk[0] = c;
	chunk[1] = '\0';
	return (str_join_free(out, ft_strdup(chunk)));
}

static char	*handle_dollar(const char *s, int *i, t_shell *shell, char *out)
{
	char	*rep;

	rep = expand_one_var(s, i, shell);
	out = str_join_free(out, rep);
	if (!out)
		return (NULL);
	return (out);
}

static char	*step(const char *s, int *i, char *out)
{
	out = append_char(out, s[*i]);
	if (!out)
		return (NULL);
	(*i)++;
	return (out);
}

char	*expand_word_impl(const char *s, t_shell *shell)
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
		state = update_quote_state(state, s[i]);
		if (s[i] == '$' && state != 1)
			out = handle_dollar(s, &i, shell, out);
		else
			out = step(s, &i, out);
		if (!out)
			return (NULL);
	}
	return (out);
}
