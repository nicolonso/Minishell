/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:40:09 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:03:48 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	int				i;

	ptr = s;
	i = 0;
	while (n-- > 0)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>

int main()
{
	char lol[] = "hhhhhhhh";
	int c = 110;
	int n = 4;
	printf("%s\n", lol);
	char *ptr = ft_memset(lol,c,n);
	printf("%s\n", ptr);
	return (0);	
}*/