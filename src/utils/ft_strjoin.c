/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:53:58 by nalfonso          #+#    #+#             */
/*   Updated: 2025/05/03 15:41:24 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	ptr = (char *)malloc(total_len);
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	ft_strlcat(ptr, s1, total_len);
	ft_strlcat(ptr, s2, total_len);
	return (ptr);
}
