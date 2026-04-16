/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:21:01 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/16 20:21:17 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_name_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_');
}

static int	is_name_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

static char	*itoa_status(int st)
{
	return (ft_itoa(st));
}

static char	*expand_one_var(const char *s, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++; /* skip '$' */
	if (s[*i] == '?')
	{
		(*i)++;
		return (itoa_status(shell->exit_status));
	}
	if (!is_name_start(s[*i]))
		return (ft_strdup("$")); /* "$" not followed by name => literal '$' */

	start = *i;
	while (s[*i] && is_name_char(s[*i]))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	if (!name)
		return (NULL);
	val = get_env_value(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup("")); /* undefined => empty */
	return (ft_strdup(val));
}

/* append `add` to `dst` and free old dst; returns new string or NULL */
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

/*
	state: 0 = unquoted, 1 = single-quoted, 2 = double-quoted
	We keep quotes for now; quote-removal can be a later step.
*/
static char	*expand_word(const char *s, t_shell *shell)
{
	int		i;
	int		state;
	char	*out;
	char	chunk[2];
	char	*rep;

	i = 0;
	state = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (state == 0 && (s[i] == '\'' || s[i] == '"'))
			state = (s[i] == '\'') ? 1 : 2;
		else if (state == 1 && s[i] == '\'')
			state = 0;
		else if (state == 2 && s[i] == '"')
			state = 0;
		if (s[i] == '$' && state != 1)
		{
			rep = expand_one_var(s, &i, shell);
			out = str_join_free(out, rep);
			if (!out)
				return (NULL);
			continue ;
		}
		chunk[0] = s[i++];
		chunk[1] = '\0';
		out = str_join_free(out, ft_strdup(chunk));
		if (!out)
			return (NULL);
	}
	return (out);
}

int	expand_tokens(t_token *tok, t_shell *shell)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && tok->value)
		{
			newv = expand_word(tok->value, shell);
			if (!newv)
				return (1);
			free(tok->value);
			tok->value = newv;
		}
		tok = tok->next;
	}
	return (0);
}
