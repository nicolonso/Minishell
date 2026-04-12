/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:07:31 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/12 21:51:59 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = strdup(value);
			return ;
		}
		env = env->next;
	}	
}

static int   env_len(t_env *env)
{
    int n;

    n = 0;
    while (env)
    {
        n++;
        env = env->next;
    }
    return (n);
}

static char  *env_entry(t_env *node)
{
    char    *tmp;
    char    *entry;

    tmp   = ft_strjoin(node->key, "=");
    entry = ft_strjoin(tmp, node->value ? node->value : "");
    free(tmp);
    return (entry);
}

char    **env_to_arr(t_env *env)
{
    char    **arr;
    int     n;
    int     i;

    n   = env_len(env);
    arr = ft_calloc(n + 1, sizeof(char *));
    if (!arr)
        return (NULL);
    i = 0;
    while (env)
    {
        arr[i] = env_entry(env);
        if (!arr[i])
        {
            ft_free_split(arr);
            return (NULL);
        }
        env = env->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}
