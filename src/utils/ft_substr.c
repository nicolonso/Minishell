#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *p = NULL;
	size_t	len_s = ft_strlen(s);
	size_t i = 0;

	if ( !len || start > len_s)
		return ft_strdup("");
	if (len > len_s - start)
		len = len_s - start;
	p = malloc(len + 1);
	if (!p)
		return NULL;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = 0;
	
	return p;
}
