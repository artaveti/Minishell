
#include "lib_for_minishell.h"

void ft_dup2_stdin(t_token_list *redir_list, int *fd_redir, int **heredoc_pipe);
void ft_dup2_stdout(t_token_list *redir_list, int *fd_redir);

void ft_change_stdin_stdout_fd_pipe(int **fd_arr, int fd_quant_pipe, int i)
{
  int i_mid;

  if (fd_arr == NULL)
    return ;
  i_mid = i / 2;
  if (i == 0)
    dup2(fd_arr[i][1], STDOUT_FILENO);
  else if (i == fd_quant_pipe)
    dup2(fd_arr[i - 1][0], STDIN_FILENO);
  else
  {
    dup2(fd_arr[i_mid][0], STDIN_FILENO);
    dup2(fd_arr[i][1], STDOUT_FILENO);
  }
  return ;
}



void ft_change_stdin_stdout_fd_redir(t_token_list *redir_list, int *fd_redir, int **heredoc_pipe)
{
  if (redir_list == NULL)
    return;
  if (redir_list->type == START)
    redir_list = redir_list->next;
  while(redir_list != NULL && redir_list->type != START)
  {
    ft_dup2_stdin(redir_list, fd_redir, heredoc_pipe);
    ft_dup2_stdout(redir_list, fd_redir);
    redir_list = redir_list->next;
  }
  return ;
}



void ft_dup2_stdin(t_token_list *redir_list, int *fd_redir, int **heredoc_pipe)
{
    char *error_str;
    int num;
    
    error_str = NULL;
    if (redir_list->type == REDIR_INT)
    {
      fd_redir[0] = open(redir_list->value, O_RDONLY, 0644);
      if (fd_redir[0] < 0)
      {
        error_str = ft_strjoin("minishell: ", redir_list->value);
        perror(error_str);
        free(error_str);
        exit_status_msh = 1;
        exit(EXIT_ERROR_NO_FILE_OR_DIRECTORY);
      }
      dup2(fd_redir[0], STDIN_FILENO);
      close(fd_redir[0]);
    }
    else if (redir_list->type == HEREDOC)
    {
      num = ft_atoi(redir_list->value);
      dup2(heredoc_pipe[num][0], STDIN_FILENO);
    }
return ;
}



void ft_dup2_stdout(t_token_list *redir_list, int *fd_redir)
{
    if (redir_list->type == REDIR_OUT)
    {
      fd_redir[1] = open(redir_list->value, O_RDWR | O_TRUNC, 0644);
      dup2(fd_redir[1], STDOUT_FILENO);
      close(fd_redir[1]);
    }
    else if (redir_list->type == REDIR_APPEND)
    {
      fd_redir[2] = open(redir_list->value, O_RDWR | O_APPEND, 0644);
      dup2(fd_redir[2], STDOUT_FILENO);
      close(fd_redir[2]);
    }
return ;
}
