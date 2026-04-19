/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:54 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/19 17:50:15 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	clean_exit(t_shell *shell, int code)
{
	rl_clear_history();
	free_env(shell->env);
	exit(code);
}

int	ft_built_exit(char **av, t_shell *shell)
{
	int	code;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!av[1])
	{
		clean_exit(shell, shell->exit_status);
	}
	if (av[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (!is_numeric(av[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
		clean_exit(shell, 2);
	}
	code = ft_atoi(av[1]) & 255;
	clean_exit(shell, code);
	return (0);
}
