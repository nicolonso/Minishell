/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:21:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/17 06:39:15 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*parse_input(char *str, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(str);
	if (!tokens)
		return (parse_tokenize_error(str, shell), NULL);
	if (validate_tokens(tokens) != 0)
		return (free_tokens(tokens), parse_validate_error(shell), NULL);
	if (expand_tokens(tokens, shell) != 0)
	return (free_tokens(tokens), NULL);
	remove_quotes_tokens(tokens);
	remove_empty_words(&tokens);
	cmds = parse_build_cmds(tokens, shell);
	free_tokens(tokens);
	return (cmds);
}
