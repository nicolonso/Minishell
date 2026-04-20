/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:44:29 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:41 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	copy_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	copy_len = 0;
	if (size != 0)
	{
		while (src[copy_len] && copy_len < (size - 1))
		{
			dst[copy_len] = src[copy_len];
			copy_len++;
		}
		dst[copy_len] = '\0';
	}
	return (src_len);
}

/*#include <stdio.h>

int main()
{
	char str1[19] = "Hello ";
	char *str2 = "baby lol";
	size_t size = 9;
	size_t lenght = ft_strlcpy(str1, str2, size);
	
	printf("%zu\n", lenght);
	printf("%s\n", str1);
	return (0);
}*/