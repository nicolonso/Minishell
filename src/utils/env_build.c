/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:13:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/19 13:36:17 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

static t_env	*create_env_node(char *str)
{
	t_env	*node;
	char	*eq;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		node->key = ft_strndup(str, eq - str);
		node->value = ft_strdup(eq + 1);
	}
	else
		node->key = ft_strdup(str);
	return (node);
}

static void	add_env_node(t_env **head, t_env **last, t_env *node)
{
	if (!*head)
		*head = node;
	else
		(*last)->next = node;
	*last = node;
}

t_env	*build_env(char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
			return (head);
		add_env_node(&head, &last, node);
		i++;
	}
	return (head);
}
