/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:49:42 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/10 14:46:08 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

// Libraries

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

#include <signal.h>

# include "utils/history.h"
# include "utils/str.h"
# include "utils/mem.h"


# include "parse/parse.h"
# include "parse/token.h"


# include "execute/execute.h"

// Parsing
typedef struct s_cmd
{
	char			**av;
	struct s_cmd	*next;
}	t_cmd;


// Functions



#endif
