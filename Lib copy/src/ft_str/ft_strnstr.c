/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:45:23 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:59 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	j;
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < n)
	{
		j = 0;
		while (little[j] && (i + j) < n && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>

int main()
{
	char *str = "You need to find me Ahahahhaha you got it";
	char *find = "Ahahahha";
	int n = 35;
	char *result = ft_strnstr(str,find, n);
	
	printf("%s\n", result);
	return (0);
}*/