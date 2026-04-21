/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:21:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/20 12:25:14 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (free_tokens(tokens), NULL);
	remove_quotes_tokens(tokens);
	remove_empty_words(&tokens);
	cmds = parse_build_cmds(tokens, shell);
	free_tokens(tokens);
	return (cmds);
}
