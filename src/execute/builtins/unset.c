/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:06:14 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 22:11:24 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/* static void unset_helper()
{
	
} */

int     ft_built_unset(char **av, t_shell *shell)
{
    t_env   *cur;
    t_env   *prev;
    int     i;

    i = 1;
    while (av[i])
    {
        cur  = shell->env;
        prev = NULL;
        while (cur)
        {
            if (ft_strcmp(cur->key, av[i]) == 0)
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
            cur  = cur->next;
        }
        i++;
    }
    return (0);
}
