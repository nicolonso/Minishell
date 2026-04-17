/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:53:58 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:30 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

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

/*#include <stdio.h>

int main()
{
	char *str1 = "Hello ";
	char *str2 = "baby lol";
	char *ptr = ft_strjoin(str1, str2);

	//ft_putendl_fd(ptr, 1);
	printf("%s\n", ptr);
	return (0);
}*/