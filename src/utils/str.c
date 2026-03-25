/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:07:26 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/03/13 21:35:24 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlen(char *s)
{
    size_t  i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}

int		ft_strncmp(char *s1, const char *s2, int n)
{
    int  i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s1[i] == s2[i] && i < n)
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return 1;
	return 0;
}

int	ct_wds(char *str)
{
	int	i;
	int	n;
	
	i = 0;
	n = 0;
	while (str && str[i])
	{
		if (is_space(str[i]))
			i++;
		else
		{
			while (str[i] && !is_space(str[i]))
				i++;
			n++;
		}
	}
	return n;
}

