
#include "lib_for_minishell.h"

void ft_fork(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog, int i);
void ft_execve(t_for_fork *fk, t_for_prog *prog, int i);
char **ft_prog_names_join(char	**path_arr, char	*prog_name);


void ft_running_program(t_for_prog *prog, t_environment_list **envp_list)
{
    t_token_list *tmp_redir_list;
    int     check;
    int     i;

    tmp_redir_list = prog->redir_list;
    check = 0;
    i = 0;
    while (prog->argv_for_execve[i] != NULL)
    {
        while (tmp_redir_list != NULL)
        {
          if (tmp_redir_list->type == START)
            break;
          tmp_redir_list = tmp_redir_list->next;
        }
        if (i == 0 && prog->argv_for_execve[0][0] != NULL
            && prog->argv_for_execve[1] == NULL)
          ft_if_only_one_builtin(tmp_redir_list, envp_list, prog, &check);
        if (check == 0)
          ft_fork(tmp_redir_list, envp_list, prog, i);
        if (tmp_redir_list != NULL && tmp_redir_list->type == START)
          tmp_redir_list = tmp_redir_list->next;
        i++;
    }
    return ;
}



void ft_fork(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog, int i)
{
     t_for_fork fk;
     
     fk.pid = fork();
     if (fk.pid == 0)
     {
      fk.fd_out = dup(STDOUT_FILENO);
      ft_change_stdin_stdout_fd_pipe(prog->fd_arr_pipe, prog->fd_quant_pipe, i);
      ft_change_stdin_stdout_fd_redir(tmp_redir_list, fk.fd_redir, prog->fd_arr_heredoc, 0);
      ft_close_pipe_fd(prog->fd_arr_pipe, prog->fd_quant_pipe);
      ft_close_pipe_fd(prog->fd_arr_heredoc, prog->fd_quant_heredoc);
      ft_running_builtin(prog->argv_for_execve[i], envp_list, fk.fd_out, BUILTIN_EXIT);
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
		prog_paths[i] = ft_strjoin(str_backslash[i], prog_name);
		free(str_backslash[i]);
		i++;
	}
	free(str_backslash);
	return (prog_paths);
}
