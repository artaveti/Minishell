
#include "lib_for_minishell.h"

void ft_fork(char **path_arr, int **fd_arr, int fd_quant, char ***argv_for_execve,
              t_token_list *redir_list, char **envp_for_execve)
{
    int     i;
    int     j;
    pid_t   pid;
    char    **prog_paths;

    i = 0;
    while (argv_for_execve[i] != NULL)
    {
        while (redir_list != NULL)
        {
          if (redir_list->type == START)
            break;
          redir_list = redir_list->next;
        }
        pid = fork();
        if (pid == 0)
        {
          ft_creat_redir_fd(fd_arr, redir_list);
          ft_fd_close(fd_arr, fd_quant);
	        if (argv_for_execve[i][0][0] == '/' && (access(argv_for_execve[i][0], F_OK)) == 0)
            execve(argv_for_execve[i][0], argv_for_execve[i], envp_for_execve);
	        else
	        {
            prog_paths = ft_prog_names_join(path_arr, argv_for_execve[i][0]);
            j = 0;
            while (prog_paths[j] != NULL)
		        {
              if ((access(prog_paths[j], F_OK) == 0))
                execve(prog_paths[j], argv_for_execve[i], envp_for_execve);
              j++;
		        }
            printf(ERROR_COMMAND, argv_for_execve[i][0]);
	        }
	        exit(0);
        }
        if (redir_list != NULL && redir_list->type == START)
          redir_list = redir_list->next;
        i++;
    }
    return ;
}



void ft_creat_redir_fd(t_token_list *redir_list)
{

  return ;
}
	        // if (argv_for_execve[0] == NULL)
		      //   execve("", argv_for_execve, envp_for_execve);