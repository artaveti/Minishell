#include "lib_for_minishell.h"

char **ft_prog_names_join(char	**path_arr, char	*prog_name);

int ft_check_if_pid_less_than_null(t_for_prog *prog, t_for_fork *fk, int i)
{
  if (fk->pid < 0)
  {
    prog->pid_arr[i] = -1;
    return (1); 
  }
  return (0);
}

void ft_change_and_close_fd_in_fork(t_token_list *tmp_redir_list, t_for_prog *prog, t_for_fork *fk, int i)
{
  ft_change_stdin_stdout_fd_pipe(prog->fd_arr_pipe, prog->fd_quant_pipe, i);
  ft_change_stdin_stdout_fd_redir(tmp_redir_list, fk->fd_out, prog->fd_arr_heredoc, 0);
  ft_close_pipe_fd(prog->fd_arr_pipe, prog->fd_quant_pipe);
  ft_close_pipe_fd(prog->fd_arr_heredoc, prog->fd_quant_heredoc);
  return ;
}

void ft_execve(t_for_fork *fk, t_for_prog *prog, int i)
{
  int j;

  if(ft_char_find('/', prog->argv_for_execve[i][0]))
    execve(prog->argv_for_execve[i][0], prog->argv_for_execve[i], prog->envp_for_execve);
  fk->prog_paths = ft_prog_names_join(prog->path_arr, prog->argv_for_execve[i][0]);
  j = 0;
  while (fk->prog_paths != NULL && fk->prog_paths[j] != NULL)
  {
    if ((access(fk->prog_paths[j], F_OK) == 0))
      execve(fk->prog_paths[j], prog->argv_for_execve[i], prog->envp_for_execve);
      j++;
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

void ft_check_is_name_dir_or_file(t_for_fork *fk, t_for_prog *prog, int i)
{
  DIR *tmp_dir;

  if(!ft_char_find('/', prog->argv_for_execve[i][0]))
    return ;
  tmp_dir = opendir(prog->argv_for_execve[i][0]);
  if (tmp_dir == NULL)
  {
    if (access(prog->argv_for_execve[i][0], F_OK) == -1)
    {
      dup2(fk->fd_out, STDOUT_FILENO);
      printf(ERROR_NO_FILE_OR_DIR, prog->argv_for_execve[i][0]);
      exit(EXIT_ERROR_NO_FILE_OR_DIR);
    }
    else if(access(prog->argv_for_execve[i][0], X_OK) == -1)
    {
      dup2(fk->fd_out, STDOUT_FILENO);
      printf(ERROR_PERM_DEN, prog->argv_for_execve[i][0]);
      exit(EXIT_ERROR_PERM_DEN_EXEC_FILE);
    }
    return ;
  }
  closedir(tmp_dir);
  dup2(fk->fd_out, STDOUT_FILENO);
  printf(ERROR_IS_DIR, prog->argv_for_execve[i][0]);
  exit(EXIT_ERROR_NAME_IS_DIR);
}

        //printf("(fd_quant_pipe(%d)\n", prog->fd_quant_pipe);
        // if (i == 0 && prog->argv_for_execve[0][0] != NULL
        //     && prog->argv_for_execve[1] == NULL)
        //     {
        //       prog->check_builtin = BUILTIN_RETURN;
        //       ft_check_if_builtin_run(envp_list, prog, tmp_redir_list, 0);
        //     }
        