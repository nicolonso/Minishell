#include "../../include/minishell.h"
#include "../../include/parse/parse.h"
#include "../../include/utils/str.h"

void	freetab(char **tab, int k)
{
	int	i;

	i = 0;
	while (tab && i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

