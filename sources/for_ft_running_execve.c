
#include "lib_for_minishell.h"

void ft_dup2_stdin(t_token_list *redir_list, int *fd_redir);
void ft_dup2_stdout(t_token_list *redir_list, int *fd_redir);

void ft_open_pipe_fd(int **fd_arr, int fd_quant, int i)
{
  int i_mid;

  if (fd_arr == NULL)
    return ;
  i_mid = i / 2;
  if (i == 0)
    dup2(fd_arr[i][1], STDOUT_FILENO);
  else if (i == fd_quant)
    dup2(fd_arr[i - 1][0], STDIN_FILENO);
  else
  {
    dup2(fd_arr[i_mid][0], STDIN_FILENO);
    dup2(fd_arr[i][1], STDOUT_FILENO);
  }
  return ;
}



void ft_open_redir_fd(t_token_list *redir_list, int *fd_redir)
{
  if (redir_list == NULL)
    return;
  if (redir_list->type == START)
    redir_list = redir_list->next;
  while(redir_list != NULL && redir_list->type != START)
  {
    ft_dup2_stdin(redir_list, fd_redir);
    ft_dup2_stdout(redir_list, fd_redir);
    redir_list = redir_list->next;
  }
  return ;
}



void ft_dup2_stdin(t_token_list *redir_list, int *fd_redir)
{
    char *error_str;
    
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
        exit(EXIT_ERROR_NO_F_OR_D);
      }
      dup2(fd_redir[0], STDIN_FILENO);
      close(fd_redir[0]);
    }
    else if (redir_list->type == HEREDOC)
    {
      fd_redir[3] = open(redir_list->value, O_RDONLY, 0644);
      dup2(fd_redir[3], STDIN_FILENO);
      close(fd_redir[3]);
      unlink(redir_list->value);
    }
return ;
}



void ft_dup2_stdout(t_token_list *redir_list, int *fd_redir)
{
    if (redir_list->type == REDIR_OUT)
    {
      fd_redir[1] = open(redir_list->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
      dup2(fd_redir[1], STDOUT_FILENO);
      close(fd_redir[1]);
    }
    else if (redir_list->type == REDIR_APPEND)
    {
      fd_redir[2] = open(redir_list->value, O_CREAT | O_RDWR | O_APPEND, 0644);
      dup2(fd_redir[2], STDOUT_FILENO);
      close(fd_redir[2]);
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
