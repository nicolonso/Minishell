/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:48:44 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/17 10:51:40 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
//	while (1)
//	{
		// Read Line
	prompt_loop();
		// Parse Line
		// Execute command 
//	}
	return (0);
} */

static void	add_env_node(t_env **head, t_env **last, char *entry)
{
	t_env	*node;
	char	*eq;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return ;
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		node->key = ft_strndup(entry, eq - entry);
		node->value = ft_strdup(eq + 1);
	}
	else
		node->key = ft_strdup(entry);
	if (!*head)
		*head = node;
	else
		(*last)->next = node;
	*last = node;
}

static t_env	*build_env(char **envp)
{
	t_env	*head;
	t_env	*last;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_node(&head, &last, envp[i]);
		i++;
	}
	return (head);
}

void	free_env(t_env *env)
{
    t_env   *next;

    while (env)
    {
        next = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = next;
    }
}

int     main(int ac, char **av, char **envp)
{
    t_shell shell;

    (void)ac;
    (void)av;
    shell.env         = build_env(envp);
    shell.env_arr     = NULL;
    shell.exit_status = 0;
    prompt_loop(&shell);
	free_env(shell.env);
    return (shell.exit_status);
}
