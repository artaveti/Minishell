
#include "lib_for_minishell.h"

int ft_input_to_heredoc(t_token_list *heredoc_list, t_environment_list *envp_list, int **fd_arr_heredoc)
{
  pid_t heredoc_fork;
  int status_heredoc;
  int  i;
  
  status_heredoc = 0;
  heredoc_fork = fork();
  if (heredoc_fork == 0)
  {
    signal(SIGINT, ft_sigint_heredoc); //exit(EXIT_HEREDOC_SIGINT);
    i = 0;
    heredoc_list = heredoc_list->next;
    while (heredoc_list != NULL)
    {
      ft_readline_for_heredoc(heredoc_list->type, heredoc_list->value, fd_arr_heredoc[i][1], envp_list);
      i++;
      heredoc_list = heredoc_list->next;
    }
//system("leaks minishell");
    exit(EXIT_SUCCESS);
  }
  waitpid(heredoc_fork, &status_heredoc, 0);
  WIFEXITED(status_heredoc);
  if (WEXITSTATUS(status_heredoc) == EXIT_HEREDOC_SIGINT)
  {
    g_exit_status_msh = EXIT_HEREDOC_SIGINT;
    return (EXIT_HEREDOC_SIGINT);
  }
  return (0);
}



void  ft_readline_for_heredoc(int type, char *string, int fd_num, t_environment_list *envp_list)
{
  char *heredoc_line;

  heredoc_line = NULL;
  heredoc_line = readline("heredoc_minishell>");
  while (heredoc_line != NULL && (ft_strncmp(heredoc_line, string, ft_strlen(string))
          || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line))))
          {
            if (type == HEREDOC_W)
                ft_change_string_for_heredoc(&heredoc_line, envp_list);
            write(fd_num, heredoc_line, ft_strlen(heredoc_line));
            write(fd_num, "\n", 1);
            free(heredoc_line);
            heredoc_line = readline("heredoc_minishell>");
          }
          free(heredoc_line);
          heredoc_line = NULL;
    return ;
}



// void  ft_readline_for_heredoc(int type, char *string, int fd_num, t_environment_list *envp_list)
// {
//   char *heredoc_line;

//   heredoc_line = NULL;
//   heredoc_line = readline("heredoc_minishell>");
//   if (g_exit_status_msh == 300) //signal heredoc stop ////
// 	{
//     printf("EXIT:300\n");
//     free(heredoc_line);
//     heredoc_line = NULL;
//     system("leaks minishell");
//     exit(1);
// 	}
//   while (heredoc_line != NULL && (ft_strncmp(heredoc_line, string, ft_strlen(string))
//           || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line))))
//           {
//             // printf("(%s)\n", heredoc_line);////
//             if (type == HEREDOC_W)
//                 ft_change_string_for_heredoc(&heredoc_line, envp_list);
//             write(fd_num, heredoc_line, ft_strlen(heredoc_line));
//             write(fd_num, "\n", 1);
//             free(heredoc_line);
//             heredoc_line = readline("heredoc_minishell>");
//             if (g_exit_status_msh == 300) //signal heredoc stop ////
//             {
//               printf("EXIT:300\n");
//               free(heredoc_line);
//               heredoc_line = NULL;
//               system("leaks minishell");
//               exit(1);
//             }
//           }
//           free(heredoc_line);
//           heredoc_line = NULL;
//     return ;
// }
