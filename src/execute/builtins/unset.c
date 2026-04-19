/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:14 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/18 21:52:59 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	remove_env_node(t_shell *shell, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = shell->env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				shell->env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_built_unset(char **av, t_shell *shell)
{
	int		i;

	i = 1;
	while (av[i])
	{
		remove_env_node(shell, av[1]);
		i++;
	}
	return (0);
}
