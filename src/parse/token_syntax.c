/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:32:16 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/20 12:32:23 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_tokens(t_token *tok)
{
	t_token	*prev;

	if (!tok)
		return (0);
	if (tok->type == TOK_PIPE)
		return (-1);
	prev = NULL;
	while (tok)
	{
		if (tok->type == TOK_PIPE && tok->next && tok->next->type == TOK_PIPE)
			return (-1);
		if (is_redir_token(tok->type))
		{
			if (!tok->next || tok->next->type != TOK_WORD)
				return (-1);
		}
		prev = tok;
		tok = tok->next;
	}
	if (prev && prev->type == TOK_PIPE)
		return (-1);
	return (0);
}
