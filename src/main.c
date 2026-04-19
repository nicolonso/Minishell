/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:48:44 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/19 17:31:25 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		status;

	(void)ac;
	(void)av;
	shell.env = build_env(envp);
	shell.env_arr = NULL;
	shell.exit_status = 0;
	status = prompt_loop(&shell);
	free_env(shell.env);
	return (status);
}
