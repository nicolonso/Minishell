/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/20 11:59:56 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_print_error(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (1);
}

static int	export_valid_key(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	if (!(ft_isalpha(arg[i]) || arg[i] == '_'))
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	export_add_or_update(t_shell *shell, char *arg)
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

static void	export_print_all(t_shell *shell)
{
	t_env	*e;

	e = shell->env;
	while (e)
	{
		if (e->value)
			printf("declare -x %s=\"%s\"\n", e->key, e->value);
		else
			printf("declare -x %s=\"\"\n", e->key);
		e = e->next;
	}
}

int	ft_built_export(char **av, t_shell *shell)
{
	int	i;
	int	status;

	if (!av[1])
	{
		export_print_all(shell);
		return (0);
	}
	i = 1;
	status = 0;
	while (av[i])
	{
		if (!export_valid_key(av[i]))
			status = export_print_error(av[i]);
		else
			export_add_or_update(shell, av[i]);
		i++;
	}
	return (status);
}
