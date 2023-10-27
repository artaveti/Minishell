
#include "lib_for_minishell.h"

char	**ft_make_path_arr_for_execve(char	**envp)
{
	int		i;
	int		j;
	char	**path_arr;

	i = 0;
	j = 0;
	if (!envp)
	{
		return (NULL);
	}
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] == "PATH="[j])
		{
			if (j == 4)
			{
				path_arr = ft_split(ft_strchr(envp[i], '/'), ':');
				break ;
			}
			j++;
		}
		i++;
	}
	return (path_arr);
}
