/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:48:44 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/11 20:46:15 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/mini_shell.h"

int	main(int ac, char **av)
{
	char	*input;
	(void)ac;
	(void)av;
	while (1)
	{
		// Read Line
		// Parse Line
		// Execute command 
		input = readline("mini_shell$ ");
		if (!input)
			break ;
		printf("You typed: %s\n", input);
		free(input);
	}
	return (0);
}
