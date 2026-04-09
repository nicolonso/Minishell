/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:32:10 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/03/27 15:20:12 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prompt_loop(void)
{
		char	*input;
		t_token *toks;

	while (1)
	{

		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		if (!ft_strncmp(input, "exit", 4) && ((input[4])\
			== '\0' || is_space(input[4])))
		{
				free(input);
				break ;
		}
		toks = tokenize(input);
		if (!toks)
			free(input);
		print_tokens(toks);
		tok_free_all(toks);
		free(input);
	}
	clear_history();
}
