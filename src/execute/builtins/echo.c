/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:04:22 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/18 21:59:58 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_built_echo(char **av, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	newline = 1;
	i = 1;
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
