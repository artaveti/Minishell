
#include "lib_for_minishell.h"

char *ft_start_path(char c, char *string);

char    **ft_creat_envp_for_execve(t_environment_list *envp_list)
{
    char **envp_for_execve;
    char *tmp_str;
    int envp_len;
    int i;
    
    envp_len = ft_list_length_for_environment(envp_list);
    envp_for_execve = (char **)malloc(sizeof(char *) * (envp_len + 1));
    i = 0;
    while (envp_list != NULL)
    {
        envp_for_execve[i] = ft_strjoin(envp_list->name_and_value[0], "=");
        tmp_str = envp_for_execve[i];
		if (envp_list->name_and_value[1] == NULL)
			envp_for_execve[i] = ft_strjoin(envp_for_execve[i], "");
		else
			envp_for_execve[i] = ft_strjoin(envp_for_execve[i], envp_list->name_and_value[1]);
        free(tmp_str);
        envp_list = envp_list->next;
        i++;
    }
    envp_for_execve[i] = NULL;
    return (envp_for_execve);
}



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
