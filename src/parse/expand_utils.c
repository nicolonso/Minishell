/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:12:16 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/21 02:08:22 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_is_name_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_');
}

int	ms_is_name_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

int	ms_append_str(char **out, char *add)
{
	char	*newv;

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

int	ms_append_char(char **out, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ms_append_str(out, ft_strdup(tmp)));
}

void	ms_update_quote_state(char c, int *state)
{
	if (*state == 0 && (c == '\'' || c == '"'))
	{
		if (c == '\'')
			*state = 1;
		else
			*state = 2;
	}
	else if (*state == 1 && c == '\'')
		*state = 0;
	else if (*state == 2 && c == '"')
		*state = 0;
}
