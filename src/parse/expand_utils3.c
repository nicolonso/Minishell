/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:36:26 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/21 15:36:27 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_expand_dollar_heredoc(const char *s, int *i, t_shell *shell)
{
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (s[*i] >= '0' && s[*i] <= '9')
	{
		if (s[*i] == '0' && shell->prog_name)
		{
			(*i)++;
			return (ft_strdup(shell->prog_name));
		}
		(*i)++;
		return (ft_strdup(""));
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

char	*ms_expand_heredoc_word(const char *s, t_shell *shell)
{
	int		i;
	char	*out;
	char	*rep;

	i = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			rep = ms_expand_dollar_heredoc(s, &i, shell);
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
