/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:33:21 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/04/10 14:42:56 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
/*
typedef struct s_cmd {
	char **args;
	struct s_cmd *next;
} t_cmd;
*/
t_cmd *parse_cmd(char *input);

void	prompt_loop(void);
ssize_t	print_input(char *str);
char **split(char *str);
t_token	*tokenize(char *input);
void	print_tokens(t_token *toks);
