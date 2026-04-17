/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:41:39 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:03:45 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (d == s)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
		return (dest);
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
/*#include <stdio.h>

int main()
{
    char str[50] = "Hello, baby!";
    
    ft_memmove(str, str + 1, 5);
    printf( "%s\n", str);
	return (0);
}*/