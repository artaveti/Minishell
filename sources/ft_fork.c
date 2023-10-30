
#include "lib_for_minishell.h"

void ft_fork(char **path_arr, int **fd_arr, char **arr_for_execve, t_token_list *redir_list, char **envp_for_execve)
{
    int     j;
    int     i;
    pid_t   pid;
    char	**argv_for_execve;
    char    **prog_paths;

    (void)fd_arr;
    (void)redir_list;
    j = 0;
    while (arr_for_execve[j] != NULL)
    {
        pid = fork();
        if (pid == 0)
        {
          i = 0;
	      argv_for_execve = ft_split(arr_for_execve[i], ' ');
	        if (argv_for_execve[0] == NULL)
		        execve("", argv_for_execve, envp_for_execve);
	        else if (argv_for_execve[0][0] == '/' &&
		        	(access(argv_for_execve[0], F_OK)) == 0)
	        	execve(argv_for_execve[0], argv_for_execve, envp_for_execve);
	        else
	        {
		     prog_paths = ft_prog_names_join(path_arr, argv_for_execve[0]);
		     while (prog_paths[i] != NULL)
		        {
			        if ((access(prog_paths[i], F_OK) == 0))
				        execve(prog_paths[i], argv_for_execve, envp_for_execve);
                    i++;
		        }
	        }
	        return ;
        }
        j++;
    }
    return ;
}


