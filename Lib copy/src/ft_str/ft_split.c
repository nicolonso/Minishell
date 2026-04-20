/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:03:50 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/17 11:13:43 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (words);
}

static char	*ft_word_copy(char const *s, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_free_all(char **ptr, int j)
{
	while (j-- > 0)
		free(ptr[j]);
	free(ptr);
}

static char	**ft_split_words(char const *s, char c, int words, char **ptr)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		ptr[j] = ft_word_copy(s + i, len);
		if (!ptr[j])
		{
			ft_free_all(ptr, j);
			return (NULL);
		}
		i += len;
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	ptr = (char **) malloc(sizeof(char *) * (words + 1));
	if (!ptr)
		return (NULL);
	if (words == 0)
	{
		ptr[0] = NULL;
		return (ptr);
	}
	return (ft_split_words(s, c, words, ptr));
}
