
#include "lib_for_minishell.h"

void ft_readline_for_heredoc(char *string, int fd_heredoc);

int ft_fd_quant(t_token_list *token_list, int type)
{
    int fd_quant;

    fd_quant = 0;
    while(token_list != NULL)
    {
        if (token_list->type == type)
            fd_quant++;
        token_list = token_list->next;
    }
    return(fd_quant);
}



int	**ft_creat_and_open_pipes(int fd_quant_pipe)
{
	int	i;
	int	**fd_arr;

    if (fd_quant_pipe == 0)
        return (NULL);
	i = 0;
	fd_arr = (int **)malloc(sizeof(int *) * (fd_quant_pipe));
	if (!fd_arr)
	{
		perror("Can't allocate memory in ft_creat_and_open_pipes()");
		exit(EXIT_FAILURE);
	}
	while (i < fd_quant_pipe)
	{
		fd_arr[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd_arr[i])
		{
			perror("Can't allocate memory in ft_creat_and_open_pipes()");
			exit(EXIT_FAILURE);
		}
		if ((pipe(fd_arr[i]) < 0))
			perror("Can't create pipes");
		i++;
	}
	return (fd_arr);
}



void	ft_close_pipe_fd(int **fd, int fd_quant_pipe)
{
	int	i;

	i = 0;
	while (i < fd_quant_pipe)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return ;
}



void ft_input_to_heredoc(t_token_list *token_list, int **fd_arr_heredoc)
{
  int  i;
  char *num_str;
  
  i = 0;
  while (token_list != NULL)
  {
    if (token_list->type == HEREDOC)
    {
      num_str = ft_itoa(i);
      ft_readline_for_heredoc(token_list->value, fd_arr_heredoc[i][1]);
      free(token_list->value);
      token_list->value = NULL;
      token_list->value = ft_strdup(num_str);
      free(num_str);
      i++;
    }
    token_list = token_list->next;
  }
  return ;
}



void ft_readline_for_heredoc(char *string, int fd_num)
{
  char *heredoc_line;

  heredoc_line = readline("heredoc_minishell>");
  while (ft_strncmp(heredoc_line, string, ft_strlen(string))
          || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line)))
          {
            write(fd_num, heredoc_line, ft_strlen(heredoc_line));
            write(fd_num, "\n", 1);
            free(heredoc_line);
            heredoc_line = readline("heredoc_minishell>");
          }
          free(heredoc_line);
          heredoc_line = NULL;
          return ;
}
