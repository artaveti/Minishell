
#include "lib_for_minishell.h"

void ft_creat_pipe_fd(int **fd_arr, int fd_quant, int i);
void ft_creat_redir_fd(t_token_list *redir_list, int *fd_redir);
//void ft_unlink(int heredoc_quant);

void ft_running_with_pipes(char **path_arr, int **fd_arr, int fd_quant, char ***argv_for_execve,
              t_token_list *redir_list, char **envp_for_execve, t_environment_list *envp_list, int *pid_arr)
{
    int     i;
    int     j;
    int     fd_out;
    pid_t   pid;
    char    **prog_paths;
    int     *fd_redir;

    (void)envp_list;
    i = 0;
    fd_redir = (int *)malloc(sizeof(int) * 4);
    while (argv_for_execve[i] != NULL)
    {
      // arajiny steghcuma heredocnery heredoc-i jamanak stdouty talisa pipein u tpacy chi erevum, petqa arandzin sarqel jamanakavor pokhel
      // heto syntax errornery bolor depqeri hamar, ete ayn ka uremn exit
      // ete voreve forki mej chi gtnum inputi hamar faily uremn exita linum miayn ayd forky
      // kami( || ) jamanak, ete arajiny skhala(orinak` "Command not found" kam "No such file or directory"), cuyca talis u sharunakuma
      // andi ( && ) jamanak, ete arajiny skhala, el chi sharunakum
      // "bash: syntax error near unexpected token `&'" echo $? 258
      // "bash: sss: No such file or directory" echo $? 1
      // "bash: wcl: command not found" echo $? 127
      // ete grvuma "bash: (komandy, vory chka kam fayly, vory chka): u heto inchvor ban" , apa ayd jamanak cragiry ashkhatuma, hajord qaylin ancnuma"
      // isk ete grvuma "bash: miangamic patchary u symboly", apa cragiry vochmiban chi anum ev miangamic exita linum
        while (redir_list != NULL)
        {
          if (redir_list->type == START)
            break;
          redir_list = redir_list->next;
        }
        pid = fork();
        if (pid == 0)
        {
          fd_out = dup(STDOUT_FILENO);
          ft_creat_pipe_fd(fd_arr, fd_quant, i);
          ft_creat_redir_fd(redir_list, fd_redir);
          ft_fd_close(fd_arr, fd_quant);
          if (argv_for_execve[i][0] == NULL)
            exit(0);
	        else if (argv_for_execve[i][0][0] == '/' && (access(argv_for_execve[i][0], F_OK)) == 0)
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
	        }
          dup2(fd_out, STDOUT_FILENO);
          printf(ERROR_COMMAND, argv_for_execve[i][0]);
	        exit(127);
        }
        pid_arr[i] = pid;
        //printf("pid(%d)\n", pid);
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



void ft_creat_redir_fd(t_token_list *redir_list, int *fd_redir)
{
  int   i;
  char *error_str;

  if (redir_list == NULL)
    return;
  if (redir_list->type == START)
    redir_list = redir_list->next;
  error_str = NULL;
  i = 0;
  while(redir_list != NULL && redir_list->type != START)
  {
    if (redir_list->type == REDIR_INT)
    {
      fd_redir[0] = open(redir_list->value, O_RDONLY, 0644);
      if (fd_redir[0] < 0)
      {
        error_str = ft_strjoin("minishell: ", redir_list->value);
        perror(error_str);
        free(error_str);
        exit_status = 1;
        exit(1);
      }
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
      fd_redir[3] = open(redir_list->value, O_RDONLY, 0644);
      dup2(fd_redir[3], STDIN_FILENO);
      close(fd_redir[3]);
      unlink(redir_list->value);
    }
    redir_list = redir_list->next;
  }
  return ;
}



// void ft_unlink(int heredoc_quant)
// {
//   int i;
//   char *num;
//   char *filename;

//   i = 0;
//   while(i < heredoc_quant)
//   {
//     num = ft_itoa(i);
//     filename = ft_strjoin("heredoc_minishell_", num);
//     unlink(filename);
//     free(num);
//     num = NULL;
//     free(filename);
//     filename = NULL;
//     i++;
//   }
//   return ;
// }



    // else if (redir_list->type == HEREDOC)
    // {
    //   num = ft_itoa(i);
    //   filename = ft_strjoin("heredoc_minishell_", num);
    //   fd_redir[3] = open(filename, O_RDONLY, 0644);
    //   dup2(fd_redir[3], STDIN_FILENO);
    //   close(fd_redir[3]);
    //   free(num);
    //   num = NULL;
    //   free(filename);
    //   filename = NULL;
    //   i++;
    // }


