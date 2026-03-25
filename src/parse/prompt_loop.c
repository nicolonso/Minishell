/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:32:10 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/03/13 21:30:03 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prompt_loop(void)
{
		char	*input;	

	while (1)
	{

		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		if (!ft_strncmp(input, "exit", 4))
		{
				free(input);
				break ;
		}
		parse_input(input);
		free(input);
	}
	clear_history();
}
