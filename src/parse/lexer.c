 #include "../.../minishell.h"

static int	is_op(const char *s, size_t i)
{
	char c;

	c = s[i];
	return (c == '|' || c == '>' || c == '<');
}
 
size_t	read_word(const char *s, size_t	i, char	**out)
{
	enum {Q_NONE, Q_SINGLE, Q_DOUBLE} q;

	q = Q_NONE;
	t_buf b = buf_new();
	char c;
	if (!s || !out)
		return (i);
	while (s[i])
	{
		c = s[i];

		if (q == Q_NONE)
		{
			if (c == '\'')
			{
				q = Q_SINGLE;
				i++;
			}
			if (c == '"')
			{
				q = Q_DOUBLE;
				i++;
			}
			if (is_space(c) || is_op(s, i))
				break;
			buf_push(&b, c);
			i++;
		}
		else if (q == Q_SINGLE)
		{
			if (c == '\'')
			{
				q = Q_NONE;
				i++;
			}
			buf_push(&b, c);
			i++;
		}
		else if (q == Q_DOUBLE)
		{
			if (c == '"')
			{
				q = Q_NONE;
				i++;
			}
			buf_push(&b, c);
			i++;
		}	
	}
	*out = buf_take_cstr(&b);
	return i;
}
