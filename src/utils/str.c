/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:07:26 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/17 21:14:26 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	is_empty_str(const char *s)
{
	return (!s || s[0] == '\0');
}
/*
size_t	ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}
*/
int		ft_strcmp(char *s1, const char *s2)
{
    size_t  i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// ft_strlcat — needed by ft_strjoin

void    ft_free_split(char **arr)
{
    int i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

char    *ft_strndup(const char *s, size_t n)
{
    char    *dest;
    size_t  i;

    dest = ft_calloc(n + 1, sizeof(char));
    if (!dest)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        dest[i] = s[i];
        i++;
    }
    return (dest);
}
