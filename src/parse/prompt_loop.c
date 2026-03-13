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
	while (1)
	{
		char	*input;	
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!ft_strcmp(input, "exit"))
		{
				free(input);
				break ;
		}
//		if (!is_blank_line(input))
//			add_history(input);
		parse_input(input);
		free(input);
	}
}
