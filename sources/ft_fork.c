
#include "lib_for_minishell.h"

void ft_creat_pipe_fd(int **fd_arr, int fd_quant, int i);
void ft_creat_redir_fd(t_token_list *redir_list, int *fd_redir, int fd_int, int fd_out);

void ft_fork(char **path_arr, int **fd_arr, int fd_quant, char ***argv_for_execve,
              t_token_list *redir_list, char **envp_for_execve, t_environment_list *envp_list)
{
    int     i;
    int     j;
    int     fd_int;
    int     fd_out;
    pid_t   pid;
    char    **prog_paths;
    int     *fd_redir;

    (void)envp_list;
    i = 0;
    fd_redir = (int *)malloc(sizeof(int) * 4);
    while (argv_for_execve[i] != NULL)
    {
      //heredoc-i jamanak stdouty talisa pipein u tpacy chi erevum, petqa arandzin sarqel jamanakavor pokhel
        while (redir_list != NULL)
        {
          if (redir_list->type == START)
            break;
          redir_list = redir_list->next;
        }
        pid = fork();
        if (pid == 0)
        {
          fd_int = dup(STDIN_FILENO);
          fd_out = dup(STDOUT_FILENO);
          ft_creat_pipe_fd(fd_arr, fd_quant, i);
          ft_creat_redir_fd(redir_list, fd_redir, fd_int, fd_out);
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
            dup2(fd_out, STDOUT_FILENO);
            printf(ERROR_COMMAND, argv_for_execve[i][0]);
	        }
	        exit(0);
        }
        if (redir_list != NULL && redir_list->type == START)
          redir_list = redir_list->next;
        i++;
    }
    free(fd_redir);
    return ;
}



void ft_creat_pipe_fd(int **fd_arr, int fd_quant, int i)
{
  int i_mid;

  if (fd_arr == NULL)
    return ;
  i_mid = i / 2;
  if (i == 0)
    dup2(fd_arr[i][1], STDOUT_FILENO);
  else if (i == fd_quant)
    dup2(fd_arr[i_mid][0], STDIN_FILENO);
  else
  {
    dup2(fd_arr[i_mid][0], STDIN_FILENO);
    dup2(fd_arr[i][1], STDOUT_FILENO);
  }
  return ;
}



void ft_creat_redir_fd(t_token_list *redir_list, int *fd_redir, int fd_int, int fd_out)
{
  char *heredoc_line;

  if (redir_list == NULL)
    return;
  if (redir_list->type == START)
    redir_list = redir_list->next;
  while(redir_list != NULL && redir_list->type != START)
  {
    if (redir_list->type == REDIR_INT)
    {
      fd_redir[0] = open(redir_list->value, O_RDONLY, 0644);
      dup2(fd_redir[0], STDIN_FILENO);
      close(fd_redir[0]);
    }
    else if (redir_list->type == REDIR_OUT)
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
    else if (redir_list->type == HEREDOC)
    {
      dup2(fd_int, STDIN_FILENO);
      //dup2(fd_out, STDOUT_FILENO);
      fd_redir[3] = open("heredoc_minishell", O_CREAT | O_RDWR | O_TRUNC, 0644);
      heredoc_line = readline("heredoc_minishell>");
      while (ft_strncmp(heredoc_line, redir_list->value, ft_strlen(redir_list->value))
            || ft_strncmp(heredoc_line, redir_list->value, ft_strlen(heredoc_line)))
      {
        write(fd_redir[3], heredoc_line, ft_strlen(heredoc_line));
        write(fd_redir[3], "\n", 1);
        free(heredoc_line);
        heredoc_line = readline("heredoc_minishell>");
      }
      free(heredoc_line);
      close(fd_redir[3]);
      fd_redir[3] = open("heredoc_minishell", O_RDONLY, 0644);
      dup2(fd_redir[3], STDIN_FILENO);
      close(fd_redir[3]);
    }
    redir_list = redir_list->next;
  }
  unlink("heredoc_minishell");
  return ;
}


