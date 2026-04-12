/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:16:48 by nalfonso          #+#    #+#             */
/*   Updated: 2025/05/03 16:11:55 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len + 1 > 0)
	{
		if (s[len] == (char) c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}

/*#include <stdio.h>

int main()
{
	char *str = "HELLPPPPPPP!!";
	int c = 76;
	char *result = ft_strrchr(str, c);

	printf("%s\n", result);
	return (0);
}*/