/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 19:22:30 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/19 19:26:54 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_internal.h"

static int	is_valid_name_range(const char *s, int start, int end)
{
	int	j;

	if (end <= start)
		return (0);
	if (!is_name_start(s[start]))
		return (0);
	j = start;
	while (j < end)
	{
		if (!is_name_char(s[j]))
			return (0);
		j++;
	}
	return (1);
}

static char	*expand_braced(const char *s, int *i, t_shell *shell)
{
	int		start;
	int		end;
	char	*name;
	char	*val;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '}')
		(*i)++;
	if (s[*i] != '}')
		return (ft_strdup("$"));
	end = *i;
	(*i)++;
	if (!is_valid_name_range(s, start, end))
		return (ft_strdup(""));
	name = dup_key_range(s, start, end);
	if (!name)
		return (NULL);
	val = get_env_value(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*expand_one_var(const char *s, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
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
