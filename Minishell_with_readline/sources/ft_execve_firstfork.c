
#include "lib_for_minishell.h"

void	ft_execve_firstfork(char **path_arr, t_token_list **list, char **envp)
{
	t_token_list *tmp;
	char	**argv_for_execve;
	char	**prog_paths;
	int		list_len;
	int		i;

	tmp = *list;
	tmp = tmp->next;
	list_len = ft_list_length_for_token(tmp);
	argv_for_execve = (char **)malloc(sizeof(char *) * (list_len + 1));
	argv_for_execve[list_len + 1] = NULL;
	i = 0;
	while(tmp != NULL)
	{
		//printf("LIST[%d]_VALUE(%s)\n", i, tmp->value);
		argv_for_execve[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	prog_paths = ft_prog_names_join(path_arr, argv_for_execve[0]);
	while (prog_paths[i] != NULL)
	{
		if ((access(prog_paths[i], F_OK) == 0))
			execve(prog_paths[i], argv_for_execve, envp);
		i++;
	}
	return ;
}

	// i = -1;
	// if (ft_strlen(argv[1]) == 8 && !ft_strncmp(argv[1], "here_doc", 8))
	// 	argv_for_execve = ft_split(argv[3], ' ');
	// else
	// 	argv_for_execve = ft_split(argv[2], ' ');
	// if (argv_for_execve[0] == NULL)
	// 	execve("", argv_for_execve, envp);
	// else if (argv_for_execve[0][0] == '/' &&
	// 		(access(argv_for_execve[0], F_OK)) == 0)
	// 	execve(argv_for_execve[0], argv_for_execve, envp);
	// else
	// {
	// 	prog_paths = ft_prog_names_join(path_arr, argv_for_execve[0]);
	// 	while (prog_paths[++i] != NULL)
	// 	{
	// 		if ((access(prog_paths[i], F_OK) == 0))
	// 			execve(prog_paths[i], argv_for_execve, envp);
	// 	}
	// }


	// i = 1;
	// while(argv[i] != NULL)
	// 	i++;
	// argv_for_execve = (char **)malloc(sizeof(char *) * (i));
	// argv_for_execve[i - 1] = NULL;
	// i = 1;
	// while(argv[i] != NULL)
	// {
	// 	argv_for_execve[i - 1] = argv[i];
	// 	i++;
	// }
	// i = 0;
	// prog_paths = ft_prog_names_join(path_arr, argv_for_execve[0]);
	// system("leaks minishell");
	// while (prog_paths[i] != NULL)
	// {
	// 	if ((access(prog_paths[i], F_OK) == 0))
	// 		execve(prog_paths[i], argv_for_execve, envp);
	// 	i++;
	// }
	// return ;