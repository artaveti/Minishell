
#include "lib_for_minishell.h"

      // ete voreve forki mej chi gtnum inputi hamar faily uremn exita linum miayn ayd forky
      // kami( || ) jamanak, ete arajiny skhala(orinak` "Command not found" kam "No such file or directory"), cuyca talis u sharunakuma
      // andi ( && ) jamanak, ete arajiny skhala, el chi sharunakum
      // "bash: sss: No such file or directory" echo $? 1
      // "bash: wcl: command not found" echo $? 127
      // ete grvuma "bash: (komandy, vory chka kam fayly, vory chka): u heto inchvor ban" , apa ayd jamanak cragiry ashkhatuma, hajord qaylin ancnuma"
      // isk ete grvuma "bash: miangamic patchary u symboly", apa cragiry vochmiban chi anum ev miangamic exita linum

void ft_running_program(t_for_prog *prog, t_environment_list *envp_list)
{

    t_token_list *tmp_redir_list;
    int     i;
    
    //struct for fork
    pid_t   pid;
    int     fd_out;
    int     *fd_redir;
    char    **prog_paths;
    int     j;

    (void)envp_list;
    tmp_redir_list = prog->redir_list;
    fd_redir = (int *)malloc(sizeof(int) * 4);
    i = 0;
    while (prog->argv_for_execve[i] != NULL)
    {
        while (tmp_redir_list != NULL)
        {
          if (tmp_redir_list->type == START)
            break;
          tmp_redir_list = tmp_redir_list->next;
        }

        //ft_fork;
        pid = fork();
        if (pid == 0)
        {
          fd_out = dup(STDOUT_FILENO);
          ft_open_pipe_fd(prog->fd_arr, prog->fd_quant, i);
          ft_open_redir_fd(tmp_redir_list, fd_redir);
          ft_close_fd(prog->fd_arr, prog->fd_quant);
          if (prog->argv_for_execve[i][0] == NULL)
            exit(0);
	        else if (prog->argv_for_execve[i][0][0] == '/' && (access(prog->argv_for_execve[i][0], F_OK)) == 0)
            execve(prog->argv_for_execve[i][0], prog->argv_for_execve[i], prog->envp_for_execve);
	        else
	        {
            prog_paths = ft_prog_names_join(prog->path_arr, prog->argv_for_execve[i][0]);
            j = 0;
            while (prog_paths != NULL && prog_paths[j] != NULL)
		        {
              if ((access(prog_paths[j], F_OK) == 0))
                execve(prog_paths[j], prog->argv_for_execve[i], prog->envp_for_execve);
              j++;
		        }
	        }
          dup2(fd_out, STDOUT_FILENO);
          printf(ERROR_CMD_NOT_FOUND, prog->argv_for_execve[i][0]);
	        exit(EXIT_ERROR_CMD_NOT_FOUND);
        }
        prog->pid_arr[i] = pid;

        if (tmp_redir_list != NULL && tmp_redir_list->type == START)
          tmp_redir_list = tmp_redir_list->next;
        i++;
    }
    free(fd_redir);
    return ;
}



void ft_running_program(t_for_prog *prog, t_environment_list *envp_list)
{
    int     i;
    int     j;
    int     fd_out;
    pid_t   pid;
    char    **prog_paths;
    int     *fd_redir;
    t_token_list *tmp_redir_list;

    (void)envp_list;
    tmp_redir_list = prog->redir_list;
    fd_redir = (int *)malloc(sizeof(int) * 4);
    i = 0;
    while (prog->argv_for_execve[i] != NULL)
    {
        while (tmp_redir_list != NULL)
        {
          if (tmp_redir_list->type == START)
            break;
          tmp_redir_list = tmp_redir_list->next;
        }
        pid = fork();
        if (pid == 0)
        {
          fd_out = dup(STDOUT_FILENO);
          ft_open_pipe_fd(prog->fd_arr, prog->fd_quant, i);
          ft_open_redir_fd(tmp_redir_list, fd_redir);
          ft_close_fd(prog->fd_arr, prog->fd_quant);
          if (prog->argv_for_execve[i][0] == NULL)
            exit(0);
	        else if (prog->argv_for_execve[i][0][0] == '/' && (access(prog->argv_for_execve[i][0], F_OK)) == 0)
            execve(prog->argv_for_execve[i][0], prog->argv_for_execve[i], prog->envp_for_execve);
	        else
	        {
            prog_paths = ft_prog_names_join(prog->path_arr, prog->argv_for_execve[i][0]);
            j = 0;
            while (prog_paths != NULL && prog_paths[j] != NULL)
		        {
              if ((access(prog_paths[j], F_OK) == 0))
                execve(prog_paths[j], prog->argv_for_execve[i], prog->envp_for_execve);
              j++;
		        }
	        }
          dup2(fd_out, STDOUT_FILENO);
          printf(ERROR_CMD_NOT_FOUND, prog->argv_for_execve[i][0]);
	        exit(EXIT_ERROR_CMD_NOT_FOUND);
        }
        prog->pid_arr[i] = pid;
        if (tmp_redir_list != NULL && tmp_redir_list->type == START)
          tmp_redir_list = tmp_redir_list->next;
        i++;
    }
    free(fd_redir);
    return ;
}
