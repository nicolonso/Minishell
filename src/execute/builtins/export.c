/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/21 01:07:23 by nalfonso         ###   ########.fr       */
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
		return (add_without_value(shell, arg));
	key = ft_strndup(arg, eq - arg);
	value = ft_strdup(eq + 1);
	if (env_has_key(shell->env, key))
		return (update_env_value(shell->env, key, value),
			free(key), free(value), 0);
	node = new_env_node(key, value, shell->env);
	if (!node)
		return (free(key), free(value), 1);
	shell->env = node;
	return (0);
}

static void	export_print_all(t_shell *shell)
{
	t_env	**arr;
	int		n;
	int		i;

	n = count_env_nodes(shell->env);
	arr = ft_calloc(n, sizeof(t_env *));
	if (!arr)
		return ;
	fill_env_array(arr, shell->env);
	sort_env_arr(arr, n);
	i = 0;
	while (i < n)
		print_export_line(arr[i++]);
	free(arr);
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
			add_or_update(shell, av[i]);
		i++;
	}
	return (status);
}
