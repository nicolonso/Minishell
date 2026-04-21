/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 01:04:50 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/21 01:07:13 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*new_env_node(char *key, char *value, t_env *next)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = next;
	return (node);
}

int	add_without_value(t_shell *shell, char *arg)
{
	t_env	*node;

	if (env_has_key(shell->env, arg))
		return (0);
	node = new_env_node(ft_strdup(arg), NULL, shell->env);
	if (!node)
		return (1);
	shell->env = node;
	return (0);
}

void	print_export_line(t_env *env)
{
	if (env->value)
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
	else
		printf("declare -x %s\n", env->key);
}

void	fill_env_array(t_env **arr, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
}
