/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:21:01 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/17 02:25:18 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <ctype.h>

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

static int	is_name_start(char c)
{
	return (isalpha((unsigned char)c) || c == '_');
}

static int	is_name_char(char c)
{
	return (isalnum((unsigned char)c) || c == '_');
}

static char	*itoa_status(int st)
{
	char	buf[32];

	snprintf(buf, sizeof(buf), "%d", st);
	return (ft_strdup(buf));
}

static char	*dup_key_range(const char *s, int start, int end)
{
	char	*key;

	key = ft_strdup("");
	if (!key)
		return (NULL);
	while (start < end)
	{
		char	tmp[2];

		tmp[0] = s[start++];
		tmp[1] = '\0';
		key = str_join_free(key, ft_strdup(tmp));
		if (!key)
			return (NULL);
	}
	return (key);
}

static char	*expand_braced(const char *s, int *i, t_shell *shell)
{
	int		start;
	int		end;
	char	*name;
	char	*val;

	(*i)++; /* skip '{' */
	start = *i;
	while (s[*i] && s[*i] != '}')
		(*i)++;
	if (s[*i] != '}')
		return (ft_strdup("$"));
	end = *i;
	(*i)++; /* skip '}' */
	if (end <= start)
		return (ft_strdup(""));
	if (!is_name_start(s[start]))
		return (ft_strdup(""));
	{
		int	j;

		j = start;
		while (j < end)
		{
			if (!is_name_char(s[j]))
				return (ft_strdup(""));
			j++;
		}
	}
	name = dup_key_range(s, start, end);
	if (!name)
		return (NULL);
	val = get_env_value(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
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
	if (s[*i] == '{')
		return (expand_braced(s, i, shell));
	if (!is_name_start(s[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (s[*i] && is_name_char(s[*i]))
		(*i)++;
	name = dup_key_range(s, start, *i);
	if (!name)
		return (NULL);
	val = get_env_value(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

/* state: 0 = none, 1 = single-quoted, 2 = double-quoted */
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
