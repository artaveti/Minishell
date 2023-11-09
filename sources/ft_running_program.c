
#include "lib_for_minishell.h"

void ft_fork(t_token_list *tmp_redir_list, t_for_prog *prog, int i);
void ft_execve(t_for_fork *fk, t_for_prog *prog, int i);

void ft_running_program(t_for_prog *prog, t_environment_list *envp_list)
{

    t_token_list *tmp_redir_list;
    int     i;

    (void)envp_list;
    tmp_redir_list = prog->redir_list;
    i = 0;
    while (prog->argv_for_execve[i] != NULL)
    {
        while (tmp_redir_list != NULL)
        {
          if (tmp_redir_list->type == START)
            break;
          tmp_redir_list = tmp_redir_list->next;
        }
        ft_fork(tmp_redir_list, prog, i);
        if (tmp_redir_list != NULL && tmp_redir_list->type == START)
          tmp_redir_list = tmp_redir_list->next;
        i++;
    }
    return ;
}



void ft_fork(t_token_list *tmp_redir_list, t_for_prog *prog, int i)
{
     t_for_fork fk;
     
        fk.pid = fork();
        if (fk.pid == 0)
        {
          fk.fd_out = dup(STDOUT_FILENO);
          ft_open_pipe_fd(prog->fd_arr, prog->fd_quant, i);
          ft_open_redir_fd(tmp_redir_list, fk.fd_redir);
          ft_close_pipe_fd(prog->fd_arr, prog->fd_quant);
          ft_execve(&fk, prog, i);
          dup2(fk.fd_out, STDOUT_FILENO);
          printf(ERROR_CMD_NOT_FOUND, prog->argv_for_execve[i][0]);
	        exit(EXIT_ERROR_CMD_NOT_FOUND);
        }
        prog->pid_arr[i] = fk.pid;
        return ;
}



void ft_execve(t_for_fork *fk, t_for_prog *prog, int i)
{
  int j;
  
  if (prog->argv_for_execve[i][0] == NULL)
    exit(EXIT_SUCCESS);
  else if (prog->argv_for_execve[i][0][0] == '/' && (access(prog->argv_for_execve[i][0], F_OK)) == 0)
    execve(prog->argv_for_execve[i][0], prog->argv_for_execve[i], prog->envp_for_execve);
  else 
  {
    fk->prog_paths = ft_prog_names_join(prog->path_arr, prog->argv_for_execve[i][0]);
    j = 0;
    while (fk->prog_paths != NULL && fk->prog_paths[j] != NULL)
    {
      if ((access(fk->prog_paths[j], F_OK) == 0))
        execve(fk->prog_paths[j], prog->argv_for_execve[i], prog->envp_for_execve);
      j++;
    }
  }
  return ;
}
