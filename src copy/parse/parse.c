/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:21:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/20 15:26:42 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_fail(t_token *tokens)
{
	if (tokens)
		free_tokens(tokens);
	return (NULL);
}

t_cmd	*parse_input(char *str, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(str);
	if (!tokens)
	{
		parse_tokenize_error(str, shell);
		return (NULL);
	}
	if (validate_tokens(tokens) != 0)
	{
		parse_validate_error(shell);
		return (parse_fail(tokens));
	}
	if (expand_tokens(tokens, shell) != 0)
		return (parse_fail(tokens));
	if (split_expanded_tokens(&tokens) != 0)
		return (parse_fail(tokens));
	if (remove_quotes_tokens(tokens) != 0)
		return (parse_fail(tokens));
	remove_empty_words(&tokens);
	cmds = parse_build_cmds(tokens, shell);
	free_tokens(tokens);
	return (cmds);
}
