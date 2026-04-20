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
	split_expanded_tokens(&tokens);
	remove_quotes_tokens(tokens);
	remove_empty_words(&tokens);
	cmds = parse_build_cmds(tokens, shell);
	free_tokens(tokens);
	return (cmds);
}
