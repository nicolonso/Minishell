/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:48:44 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/19 13:16:27 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* static t_env	*build_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	t_env	*last;
	char	*eq;
	int		i;
	
	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		node = ft_calloc(1, sizeof(t_env));
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			node->key = ft_strndup(envp[i], eq - envp[i]);
			node->value = ft_strdup(eq + 1);
		}
		else
			node->key = ft_strdup(envp[i]);
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
} */

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
