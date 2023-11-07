
#include "lib_for_minishell.h"

char *ft_start_path(char c, char *string);

char	**ft_creat_path_argv_for_execve(char	**envp)
{
	int		i;
	int		j;
	char	**path_arr;

	i = 0;
	j = 0;
	path_arr = NULL;
	if (!envp)
		return (path_arr);
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] == "PATH="[j])
		{
			if (j == 4)
			{
				path_arr = ft_split((ft_start_path('=', envp[i]) + 1), ':');
				break ;
			}
			j++;
		}
		i++;
	}
	return (path_arr);
}



char *ft_start_path(char c, char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			return (&string[i]);
		i++;
	}
	return (NULL);
}
