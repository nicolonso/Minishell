/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:43:27 by nalfonso          #+#    #+#             */
/*   Updated: 2025/05/06 18:21:17 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		dest_len;
	int		index;

	index = 0;
	dest_len = 0;
	dest_len = (ft_strlen(s) + 1);
	dest = (char *) malloc(sizeof(char) * dest_len);
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	while (s[index])
	{
		dest[index] = s[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
