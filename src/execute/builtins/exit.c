/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:54 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/21 01:20:50 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clean_exit(t_shell *shell, int code)
{
	rl_clear_history();
	free_env(shell->env);
	exit(code);
}

static void	exit_numeric_error(t_shell *shell, char *ag)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(ag, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	clean_exit(shell, 2);
}

static int	parse_digits(char *s, int i, int sign, unsigned long long *n)
{
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		if (*n > 922337203685477580ULL)
			return (1);
		*n = *n * 10ULL + (s[i] - '0');
		if (sign == 1 && *n > 9223372036854775807ULL)
			return (1);
		if (sign == -1 && *n > 9223372036854775808ULL)
			return (1);
		i++;
	}
	return (0);
}

static int	parse_ll(char *s, long long *out)
{
	int					i;
	int					sign;
	unsigned long long	n;

	i = 0;
	sign = 1;
	n = 0;
	if (!s || !s[0])
		return (1);
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (1);
	if (parse_digits(s, i, sign, &n))
		return (1);
	if (sign == -1 && n == 9223372036854775808ULL)
		*out = -9223372036854775807LL - 1LL;
	else
		*out = sign * (long long)n;
	return (0);
}

int	ft_built_exit(char **av, t_shell *shell)
{
	long long	code;

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (!av[1])
		clean_exit(shell, shell->exit_status);
	if (av[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (parse_ll(av[1], &code) != 0)
		exit_numeric_error(shell, av[1]);
	clean_exit(shell, (unsigned char)code);
	return (0);
}
