/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:21:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/16 16:59:21 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*skip_redir(t_token *tok, t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*last;
	int		type;

	if (tok->type == TOK_REDIR_IN)
		type = REDIR_IN;
	else if (tok->type == TOK_REDIR_OUT)
		type = REDIR_OUT;
	else if (tok->type == TOK_APPEND)
		type = REDIR_APPEND;
	else
		type = HEREDOC;
	tok = tok->next;
	if (!tok || tok->type != TOK_WORD)
	{
		fprintf(stderr, "minishell: syntax error near redirection\n");
		return (NULL);
	}
	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = type;
	redir->file = ft_strdup(tok->value);
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
	return (tok->next);
}

static int	is_redir_token(int type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC);
}

static t_cmd	*build_cmd(t_token **cur)
{
	t_cmd	*cmd;
	t_token	*tok;
	int		word_count;
	int		i;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	tok = *cur;
	word_count = 0;
	while (tok && tok->type != TOK_PIPE)
	{
		if (tok->type == TOK_WORD)
			word_count++;
		else if (is_redir_token(tok->type))
			tok = tok->next;
		if (tok)
			tok = tok->next;
	}
	cmd->av = ft_calloc(word_count + 1, sizeof(char *));
	tok = *cur;
	i = 0;
	while (tok && tok->type != TOK_PIPE)
	{
		if (is_redir_token(tok->type))
		{
			tok = skip_redir(tok, cmd);
			if (!tok && i == 0)
				return (cmd);
			continue ;
		}
		if (tok->type == TOK_WORD)
			cmd->av[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	cmd->av[i] = NULL;
	if (tok && tok->type == TOK_PIPE)
		tok = tok->next;
	*cur = tok;
	return (cmd);
}

t_cmd	*parse_input(char *str, t_shell *shell)
{
	t_token	*tokens;
	t_token	*cur;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new;

	(void)shell;
	tokens = tokenize(str);
	if (!tokens)
		return (NULL);
	cur = tokens;
	head = NULL;
	tail = NULL;
	while (cur)
	{
		new = build_cmd(&cur);
		if (!new)
			break ;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
	}
	free_tokens(tokens);
	return (head);
}
