#include "../../include/minishell.h"

static char	*str_join_free(char *dst, char *add)
{
	char	*tmp;

	if (!dst || !add)
		return (free(dst), free(add), NULL);
	tmp = ft_strjoin(dst, add);
	free(dst);
	free(add);
	return (tmp);
}

/* state: 0 none, 1 single, 2 double */
static char	*remove_quotes_word(const char *s)
{
	int		i;
	int		state;
	char	*out;
	char	tmp[2];

	i = 0;
	state = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (state == 0 && (s[i] == '\'' || s[i] == '"'))
		{
			state = (s[i] == '\'') ? 1 : 2;
			i++;
			continue ;
		}
		if (state == 1 && s[i] == '\'')
		{
			state = 0;
			i++;
			continue ;
		}
		if (state == 2 && s[i] == '"')
		{
			state = 0;
			i++;
			continue ;
		}
		tmp[0] = s[i++];
		tmp[1] = '\0';
		out = str_join_free(out, ft_strdup(tmp));
		if (!out)
			return (NULL);
	}
	return (out);
}

void	remove_quotes_tokens(t_token *tok)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && tok->value)
		{
			newv = remove_quotes_word(tok->value);
			if (newv)
			{
				free(tok->value);
				tok->value = newv;
			}
		}
		tok = tok->next;
	}
}
