/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:02:17 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:03:41 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	char const	*s;

	d = dest;
	s = src;
	if (n == 0)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

/*#include <stdio.h>

int main()
{
    char *str = "Hello, baby!";
    char dest[] = "nononooongdfjgdf";
	
    ft_memcpy(str,str + 1,5);
    printf( "%s\n", dest);
	return (0);
}*/