/* **************************************************************************e*/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:21:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/25 17:57:59 by quintondell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	filltab(char **mytab, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str && str[i])
	{
		if (is_space(str[i]))
			i++;
		else
		{
			j = i;
			while (str[j] && !is_space(str[j]))
				j++;
			mytab[k] = sub_str(str, i, j - i);
			if (!mytab[k])
				return freetab(mytab, k);
			k++;
			i = j;
		}
	}
}

char **	split(char *str)
{
	char **mytab;
	int	n;

	mytab = NULL;
	n = ct_wds(str);
	mytab = malloc((n + 1) * sizeof(char *));
	mytab[n] = 0;
	if (!mytab)
		return (NULL);
	filltab(mytab, str);
	return mytab;
}

ssize_t	print_input(char *str)
{
   // return (printf("You typed this: %s\n", str));
	char	**pp;
	int	i;
	int	n;
	pp = NULL;
	pp = split(str);
	i = 0;
	n = 0;
	if (!pp)
		return -1;
	while (pp[i])
	{
		n += printf("pp%i: %s\n", i, pp[i]);
		free(pp[i]);
		i++;
	}
	free(pp);
	return n;
}
