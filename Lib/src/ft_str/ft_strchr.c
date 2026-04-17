/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:43:04 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:20 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if ((char) c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

/*#include <stdio.h>

int main()
{
	char *str = "Hellooo baby";
	int c = 101;
	char *result = ft_strchr(str, c);

	printf ("%s\n", result);
	return (0);
}*/