
add_token

static t_toktype	op_type(const char *s, size_t i)
{
	if (s[i] == '|')
		return (TOK_PIPE);
	if (s[i] == '>' && s[i + 1] == '>')
		return (TOK_APPEND);
	if (s[i] == '<' && s[i + 1] == '<')
		return (TOK_HEREDOC);
	if (s[i] == '>')
		return (TOK_REDIR_OUT);
	return (TOK_REDIR_IN);
}

size_t	tokenize_one(const char *s, size_t i, t_token **tokens)
{
	char *word;
	if (!s)
		return i;
	while (s[i] && is_space(s[i]))
		i++;
	if (!s[i])
		return (i);
	if (is_op(s, i))
	{
		len = op_len(s, i);
		add_token(tokens, op_type(s, i), NULL);
		return (i + len);
	}
	word = NULL;
	i = read_word(s, i, &word)
	if (!word)
		return (i);
	add_token(tokens, TOK_WORD, word);
	free(word);
	return (i);
}
