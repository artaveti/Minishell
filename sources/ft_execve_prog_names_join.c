
#include "lib_for_minishell.h"

char	**ft_prog_names_join(char	**path_arr, char	*prog_name)
{
	int		i;
	char	**str_backslash;
	char	**prog_paths;

	i = 0;
	if (path_arr == NULL)
		return (NULL);
	while (path_arr[i] != NULL)
		i++;
	str_backslash = (char **)malloc(sizeof(char *) * (i + 1));
	prog_paths = (char **)malloc(sizeof(char *) * (i + 1));
	str_backslash[i] = NULL;
	prog_paths[i] = NULL;
	i = 0;
	while (path_arr[i] != NULL)
	{
		str_backslash[i] = ft_strjoin(path_arr[i], "/");
		prog_paths[i] = ft_strjoin_space(str_backslash[i], prog_name);
		free(str_backslash[i]);
		i++;
	}
	free(str_backslash);
	return (prog_paths);
}
