/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:17:21 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/20 13:17:30 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by copilot          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_internal.h"

static char	*ms_dup_env_value(t_shell *shell, char *name)
{
	char	*val;

	val = get_env_value(shell->env, name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static char	*ms_expand_simple(const char *s, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*ret;

	start = *i;
	while (s[*i] && ms_is_name_char(s[*i]))
		(*i)++;
	name = ft_strndup(s + start, *i - start);
	if (!name)
		return (NULL);
	ret = ms_dup_env_value(shell, name);
	free(name);
	return (ret);
}

static char	*ms_expand_braced(const char *s, int *i, t_shell *shell)
{
	int		start;
	int		j;
	char	*name;
	char	*ret;

	start = *i;
	while (s[*i] && s[*i] != '}')
		(*i)++;
	if (s[*i] != '}')
		return (ft_strdup("$"));
	if (*i == start || !ms_is_name_start(s[start]))
		return (ft_strdup(""));
	j = start;
	while (j < *i && ms_is_name_char(s[j]))
		j++;
	if (j != *i)
		return (ft_strdup(""));
	name = ft_strndup(s + start, *i - start);
	if (!name)
		return (NULL);
	(*i)++;
	ret = ms_dup_env_value(shell, name);
	free(name);
	return (ret);
}

static char	*ms_expand_dollar(const char *s, int *i, t_shell *shell)
{
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (s[*i] == '{')
	{
		(*i)++;
		return (ms_expand_braced(s, i, shell));
	}
	if (!ms_is_name_start(s[*i]))
		return (ft_strdup("$"));
	return (ms_expand_simple(s, i, shell));
}

char	*ms_expand_word(const char *s, t_shell *shell)
{
	int		i;
	int		state;
	char	*out;
	char	*rep;

	i = 0;
	state = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		ms_update_quote_state(s[i], &state);
		if (s[i] == '$' && state != 1)
		{
			rep = ms_expand_dollar(s, &i, shell);
			if (ms_append_str(&out, rep))
				return (NULL);
			continue ;
		}
		if (ms_append_char(&out, s[i]))
			return (NULL);
		i++;
	}
	return (out);
}
