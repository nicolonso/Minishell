/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:19:24 by nalfonso          #+#    #+#             */
/*   Updated: 2025/06/12 16:47:13 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

size_t	ft_strlen_nl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_check_nl(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
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

char	*ft_strjoin_gn(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*ptr;

	l1 = ft_strlen_nl(s1);
	l2 = ft_strlen_nl(s2);
	ptr = malloc(l1 + l2 + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1 && i < l1)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && i < l2)
	{
		ptr[l1 + i] = s2[i];
		i++;
	}
	ptr[l1 + l2] = '\0';
	free(s1);
	return (ptr);
}

char	*buffer_rest(char *buffer)
{
	int	i;
	int	j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
	if (j == 0)
		return (free(buffer), NULL);
	return (buffer);
}

char	*extract_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}
