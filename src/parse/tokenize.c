/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 19:16:33 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/19 19:16:35 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_internal.h"

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

static int	read_operator(const char *s, int i, t_token **head)
{
	if (s[i] == '|')
	{
		tok_append(head, tok_new(TOK_PIPE, ft_strdup("|")));
		return (i + 1);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		tok_append(head, tok_new(TOK_HEREDOC, ft_strdup("<<")));
		return (i + 2);
	}
	if (s[i] == '>' && s[i + 1] == '>')
	{
		tok_append(head, tok_new(TOK_APPEND, ft_strdup(">>")));
		return (i + 2);
	}
	if (s[i] == '<')
	{
		tok_append(head, tok_new(TOK_REDIR_IN, ft_strdup("<")));
		return (i + 1);
	}
	tok_append(head, tok_new(TOK_REDIR_OUT, ft_strdup(">")));
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
	tok_append(head, tok_new(TOK_WORD, ft_strdup(buf)));
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
