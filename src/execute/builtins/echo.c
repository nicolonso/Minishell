/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:04:22 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/21 00:42:04 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || !s[1])
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_built_echo(char **av, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	newline = 1;
	i = 1;
	while (av[i] && is_n_flag(av[i]))
	{
		newline = 0;
		i++;
	}
	while (av[i])
	{
		write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
