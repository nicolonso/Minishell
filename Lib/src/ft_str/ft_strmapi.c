/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:22:05 by nalfonso          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:50 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	i;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	ptr = (char *) malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*char uppercase_odd_chars(unsigned int i, char c)
{
    if (i % 2 == 1)
        return (c >= 'a' && c <= 'z') ? c - 32 : c;
    return (c);
}

int main()
{
    const char *str = "hello";
    char *result = ft_strmapi(str, uppercase_odd_chars);
	
    if (result)
	{
        printf("Original: %s\n", str);
        printf("Modified: %s\n", result);
        free(result);
    }
    return (0);
}*/