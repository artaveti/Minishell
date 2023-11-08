
#include "lib_for_minishell.h"

void ft_readline_for_heredoc(char *string, int fd_heredoc);

void ft_creat_heredoc(t_token_list *token_list)
{
  char *num_str;
  char *filename;
  int  fd_heredoc;
  int  i;

  i = 0;
  while (token_list != NULL)
  {
    if (token_list->type == HEREDOC)
    {
      num_str = ft_itoa(i);
      filename = ft_strjoin("heredoc_minishell_", num_str);
      fd_heredoc = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
      ft_readline_for_heredoc(token_list->value, fd_heredoc);
      free(token_list->value);
      token_list->value = NULL;
      token_list->value = ft_strdup(filename);
      free(num_str);
      free(filename);
      close(fd_heredoc);
      i++;
    }
    token_list = token_list->next;
  }
  return ;
}



void ft_readline_for_heredoc(char *string, int fd_heredoc)
{
  char *heredoc_line;

  heredoc_line = readline("heredoc_minishell>");
  while (ft_strncmp(heredoc_line, string, ft_strlen(string))
          || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line)))
          {
            write(fd_heredoc, heredoc_line, ft_strlen(heredoc_line));
            write(fd_heredoc, "\n", 1);
            free(heredoc_line);
            heredoc_line = readline("heredoc_minishell>");
          }
          free(heredoc_line);
          heredoc_line = NULL;
          return ;
}
