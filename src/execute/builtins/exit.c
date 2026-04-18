/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:54 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/17 00:00:00 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Returns 1 if the string is a valid integer (optional leading +/-
** followed by at least one digit), 0 otherwise.
** Examples:
**   "42"   -> 1    (valid)
**   "-5"   -> 1    (valid)
**   "+10"  -> 1    (valid)
**   "abc"  -> 0    (invalid: not a number)
**   "12ab" -> 0    (invalid: trailing letters)
**   ""     -> 0    (invalid: empty string)
*/
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

/*
** Cleans up all heap memory the shell owns, then exits.
** Called from ft_built_exit so valgrind sees a clean exit.
*/
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
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			av[1]);
		clean_exit(shell, 2);
	}
	code = ft_atoi(av[1]) & 255;
	clean_exit(shell, code);
	return (0);
}
