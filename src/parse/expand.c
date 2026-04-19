#include "minishell.h"
#include "parse_internal.h"

static int	update_quote_state(int state, char c)
{
	if (state == 0 && (c == '\'' || c == '"'))
	{
		if (c == '\'')
			return (1);
		return (2);
	}
	if (state == 1 && c == '\'')
		return (0);
	if (state == 2 && c == '"')
		return (0);
	return (state);
}

static char	*expand_braced(const char *s, int *i, t_shell *shell)
{
	int		start;
	int		end;
	int		j;
	char	*name;
	char	*val;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '}')
		(*i)++;
	if (s[*i] != '}')
		return (ft_strdup("$"));
	end = *i;
	(*i)++;
	if (end <= start)
		return (ft_strdup(""));
	if (!is_name_start(s[start]))
		return (ft_strdup(""));
	j = start;
	while (j < end)
	{
		if (!is_name_char(s[j]))
			return (ft_strdup(""));
		j++;
	}
	name = dup_key_range(s, start, end);
	if (!name)
		return (NULL);
	val = get_env_value(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static char	*expand_one_var(const char *s, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (itoa_status(shell->exit_status));
	}
	if (s[*i] == '{')
		return (expand_braced(s, i, shell));
	if (!is_name_start(s[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (s[*i] && is_name_char(s[*i]))
		(*i)++;
	name = dup_key_range(s, start, *i);
	if (!name)
		return (NULL);
	val = get_env_value(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static char	*append_char(char *out, char c)
{
	char	chunk[2];

	chunk[0] = c;
	chunk[1] = '\0';
	return (str_join_free(out, ft_strdup(chunk)));
}

static char	*expand_word(const char *s, t_shell *shell)
{
	int		i;
	int		state;
	char	*out;
	char	*rep;

	i = 0;
	state = 0;
	out = ft_strdup("");
	if (!out)
		return (NULL);
	while (s[i])
	{
		state = update_quote_state(state, s[i]);
		if (s[i] == '$' && state != 1)
		{
			rep = expand_one_var(s, &i, shell);
			out = str_join_free(out, rep);
			if (!out)
				return (NULL);
			continue ;
		}
		out = append_char(out, s[i]);
		if (!out)
			return (NULL);
		i++;
	}
	return (out);
}

int	expand_tokens(t_token *tok, t_shell *shell)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && tok->value)
		{
			newv = expand_word(tok->value, shell);
			if (!newv)
				return (1);
			free(tok->value);
			tok->value = newv;
		}
		tok = tok->next;
	}
	return (0);
}