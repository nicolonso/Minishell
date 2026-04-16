/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/16 20:19:47 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*new_token(int type, char *value)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

static void	token_append(t_token **head, t_token *new)
{
	t_token	*cur;

	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	free_tokens(t_token *tok)
{
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		free(tok->value);
		free(tok);
		tok = next;
	}
}

static int	read_quoted(const char *s, int i, char *buf, int *len)
{
	char	quote;

	quote = s[i];
	if (*len >= 4095)
		return (-1);
	buf[(*len)++] = s[i++];
	while (s[i] && s[i] != quote)
	{
		if (*len >= 4095)
			return (-1);
		buf[(*len)++] = s[i++];
	}
	if (s[i] != quote)
		return (-1);
	if (*len >= 4095)
		return (-1);
	buf[(*len)++] = s[i++];
	return (i);
}

static int	read_operator(const char *s, int i, t_token **head)
{
	if (s[i] == '|')
	{
		token_append(head, new_token(TOK_PIPE, ft_strdup("|")));
		return (i + 1);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		token_append(head, new_token(TOK_HEREDOC, ft_strdup("<<")));
		return (i + 2);
	}
	if (s[i] == '>' && s[i + 1] == '>')
	{
		token_append(head, new_token(TOK_APPEND, ft_strdup(">>")));
		return (i + 2);
	}
	if (s[i] == '<')
	{
		token_append(head, new_token(TOK_REDIR_IN, ft_strdup("<")));
		return (i + 1);
	}
	token_append(head, new_token(TOK_REDIR_OUT, ft_strdup(">")));
	return (i + 1);
}

static int	read_word(const char *s, int i, t_token **head)
{
	char	buf[4096];
	int		len;
	int		next_i;

	len = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t'
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			next_i = read_quoted(s, i, buf, &len);
			if (next_i < 0)
				return (-1);
			i = next_i;
		}
		else
		{
			if (len >= 4095)
				return (-1);
			buf[len++] = s[i++];
		}
	}
	buf[len] = '\0';
	token_append(head, new_token(TOK_WORD, ft_strdup(buf)));
	return (i);
}

t_token	*tokenize(const char *input)
{
	t_token	*head;
	int		i;
	int		next_i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = read_operator(input, i, &head);
		else
		{
			next_i = read_word(input, i, &head);
			if (next_i < 0)
			{
				free_tokens(head);
				return (NULL);
			}
			i = next_i;
		}
	}
	return (head);
}
