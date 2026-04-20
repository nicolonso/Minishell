/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:48:17 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:05:11 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

static int	ft_check(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_check (set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_check (set, s1[end - 1]))
		end--;
	ptr = (char *)malloc((end - start) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (start < end)
		ptr[i++] = s1[start++];
	ptr[i] = '\0';
	return (ptr);
}

/*#include <stdio.h>

int main()
{
	char *str1 = "  Magic!  ";
	char *set = "  ,";
	char *result = ft_strtrim(str1, set);

	printf("%s\n", result);
	return (0);
}*/