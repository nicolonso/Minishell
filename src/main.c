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

#include "minishell.h"

static char	*get_prog_name(char *av0)
{
	char	*slash;

	if (!av0)
		return (ft_strdup("minishell"));
	slash = ft_strrchr(av0, '/');
	if (slash)
		return (ft_strdup(slash + 1));
	return (ft_strdup(av0));
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		status;

	(void)ac;
	shell.env = build_env(envp);
	shell.env_arr = NULL;
	shell.exit_status = 0;
	if (av[0])
		shell.prog_name = get_prog_name(av[0]);
	else
		shell.prog_name = get_prog_name(NULL);
	status = prompt_loop(&shell);
	free(shell.prog_name);
	free_env(shell.env);
	return (status);
}
