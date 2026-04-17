/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:44:13 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:34 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	buffer;
	size_t	copy_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	copy_len = 0;
	buffer = (size - dest_len - 1);
	while (src[copy_len] && copy_len < buffer)
	{
		dst[dest_len + copy_len] = src[copy_len];
		copy_len++;
	}
	dst[dest_len + copy_len] = '\0';
	return (dest_len + src_len);
}

/*#include <stdio.h>

int main()
{
	char str1[19] = "Hello ";
	char *str2 = "baby lol";
	size_t lenght = ft_strlcat(str1, str2, sizeof(str1));
	
	printf("%zu\n", lenght);
	printf("%s\n", str1);
	return (0);
}*/