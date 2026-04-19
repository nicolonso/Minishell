/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:05:54 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/18 21:20:44 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_built_exit(char **av, t_shell *shell)
{
	int	code;

	printf("exit\n");
	if (!av[1])
		code = shell->exit_status;
	else if (av[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else
		code = atoi(av[1]) & 255;
	exit(code);
}
