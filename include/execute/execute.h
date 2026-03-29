#ifndef EXECUTE_H
# define EXECUTE_H

// Libraries

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Structures 

typedef struct s_cmd
{
	char			**av;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;	
}	t_env;

typedef struct s_shell
{
	t_env			*env;
	int				exit_status;
}	t_shell;

// CD FUNCTION

int		ft_built_cd(char **av, t_shell *shell);
char	*get_env_value(t_env *env, char *key);

// ---------------- Execute -------------------

# endif
