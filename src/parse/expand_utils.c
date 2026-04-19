#include "minishell.h"

int	is_name_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_');
}

int	is_name_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

char	*str_join_free(char *dst, char *add)
{
	char	*tmp;

	if (!dst || !add)
		return (free(dst), free(add), NULL);
	tmp = ft_strjoin(dst, add);
	free(dst);
	free(add);
	return (tmp);
}

char	*itoa_status(int st)
{
	char	buf[32];

	snprintf(buf, sizeof(buf), "%d", st);
	return (ft_strdup(buf));
}

char	*dup_key_range(const char *s, int start, int end)
{
	char	*key;
	char	tmp[2];

	key = ft_strdup("");
	if (!key)
		return (NULL);
	while (start < end)
	{
		tmp[0] = s[start++];
		tmp[1] = '\0';
		key = str_join_free(key, ft_strdup(tmp));
		if (!key)
			return (NULL);
	}
	return (key);
}