/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/18 22:09:11 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	add_or_update(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;
	t_env	*node;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	key = ft_strndup(arg, eq - arg);
	value = ft_strdup(eq + 1);
	if (get_env_value(shell->env, key))
	{
		update_env_value(shell->env, key, value);
		free(key);
		free(value);
		return (0);
	}
	node = ft_calloc(1, sizeof(t_env));
	node->key = key;
	node->value = value;
	node->next = shell->env;
	shell->env = node;
	return (0);
}

int	ft_built_export(char **av, t_shell *shell)
{
	t_env	*e;
	int		i;

	if (!av[1])
	{
		e = shell->env;
		while (e)
		{
			if (e->value)
				printf("declare -x %s=\"%s\"\n", e->key, e->value);
			else
				printf("declare -x %s=\"\"\n", e->key);
			e = e->next;
		}
		return (0);
	}
	i = 1;
	while (av[i])
		add_or_update(shell, av[i++]);
	return (0);
}
