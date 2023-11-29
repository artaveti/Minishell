
#include "lib_for_minishell.h"

void ft_input_to_heredoc(t_token_list *heredoc_list, t_environment_list *envp_list, int **fd_arr_heredoc)
{
  int  i;
  
  i = 0;
  heredoc_list = heredoc_list->next;
  while (heredoc_list != NULL)
  {
    ft_readline_for_heredoc(heredoc_list->type, heredoc_list->value, fd_arr_heredoc[i][1], envp_list);
    i++;
    heredoc_list = heredoc_list->next;
  }
  return ;
}



void ft_readline_for_heredoc(int type, char *string, int fd_num, t_environment_list *envp_list)
{
  char *heredoc_line;

  heredoc_line = readline("heredoc_minishell>");
  while (ft_strncmp(heredoc_line, string, ft_strlen(string))
          || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line)))
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
