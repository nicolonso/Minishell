/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:21:01 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/20 12:33:37 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_token_needs_split(t_token *tok)
{
	if (!tok || tok->type != TOK_WORD || !tok->value)
		return (0);
	if (ft_has_charset(tok->value, "'\""))
		return (0);
	if (ft_has_charset(tok->value, " \t"))
		return (1);
	return (0);
}

int	expand_tokens(t_token *tok, t_shell *shell)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && tok->value)
		{
			newv = ms_expand_word(tok->value, shell);
			if (!newv)
				return (1);
			free(tok->value);
			tok->value = newv;
		}
		tok = tok->next;
	}
	return (0);
}
