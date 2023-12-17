
#include "lib_for_minishell.h"



void	heredoc_sig(int sig)////
{
  (void)sig;

	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
  exit_status_msh = 300;
}



void ft_input_to_heredoc(t_token_list *heredoc_list, t_environment_list *envp_list, int **fd_arr_heredoc)
{
  int  i;
  
  //exit_status_msh = 0;
  i = 0;
  heredoc_list = heredoc_list->next;

  handleterm(0); //signal heredoc stop ////
  signal(SIGINT, heredoc_sig);////


  while (heredoc_list != NULL)
  {
    ft_readline_for_heredoc(heredoc_list->type, heredoc_list->value, fd_arr_heredoc[i][1], envp_list);
    i++;
    heredoc_list = heredoc_list->next;
  }
  //  if (exit_status_msh == 1) //signal heredoc stop
  //  {
  //   printf("Returned to main\n");
  //  // signal(SIGINT, inthandle);
  //  }
  return ;
}



void ft_readline_for_heredoc(int type, char *string, int fd_num, t_environment_list *envp_list)
{
  char *heredoc_line;

  heredoc_line = readline("heredoc_minishell>");


  if (!heredoc_line) //stop ctrl-d////
    return ;


  while (ft_strncmp(heredoc_line, string, ft_strlen(string))
          || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line)))
          {
            if (type == HEREDOC_W)
                ft_change_string_for_heredoc(&heredoc_line, envp_list);
            write(fd_num, heredoc_line, ft_strlen(heredoc_line));
            write(fd_num, "\n", 1);
            free(heredoc_line);



  if (exit_status_msh == 300) //signal heredoc stop ////
	{
    printf("HEE\n");
		return ;
	}



            heredoc_line = readline("heredoc_minishell>");

    if (!heredoc_line) //stop ctrl-d////
    return ;


          }
          free(heredoc_line);
          heredoc_line = NULL;
          return ;
}
