
#include "lib_for_minishell.h"

void ft_readline_for_heredoc(int type, char *string, int fd_num, t_environment_list *envp_list);
void ft_change_string_for_heredoc(char **heredoc_line, t_environment_list *envp_list);
void ft_lexer_for_heredoc(char *input_str, t_token_list *string_list);
void ft_is_token_sep_for_heredoc(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_word_for_heredoc(int *i, char *input_str, t_token_list *token_list);
void ft_parser_change_dollar_for_heredoc(t_token_list **list, t_environment_list *envp_list);

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



void ft_change_string_for_heredoc(char **heredoc_line, t_environment_list *envp_list)
{
  t_token_list *string_list;
  t_token_list *tmp_list;

  string_list = ft_list_creat_token();
  ft_lexer_for_heredoc(*heredoc_line, string_list);
  ft_parser_change_dollar_for_heredoc(&string_list, envp_list);
  free(*heredoc_line);
  *heredoc_line = NULL;
  tmp_list = string_list;
  while(tmp_list != NULL)
  {
    heredoc_line
    tmp_list = tmp_list->next;
  }
  //ft_list_iter_printf_token(string_list, printf); ////////////////////////////////////////
  return ;
}



void ft_lexer_for_heredoc(char *input_str, t_token_list *string_list)
{
    int i;
    
    i = 0;
    if (input_str == NULL)
        return ;
    while (input_str[i] != '\0')
    {
        ft_is_token_sep_for_heredoc(&i, input_str, string_list);
        ft_is_token_word_for_heredoc(&i, input_str, string_list);
    }
    return ;
}



void ft_is_token_sep_for_heredoc(int *i, char *input_str, t_token_list *token_list)
{
    t_token_list *tmp;

    if (ft_strchr(WHITESPACES, input_str[*i]))
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = SEP;
        tmp->value = ft_strdup(" ");
        tmp->next = NULL;
        // while(ft_strchr(WHITESPACES, input_str[*i]) && input_str[*i] != '\0')
        //     *i = *i + 1;
        *i = *i + 1;
        ft_list_add_back_for_token(&token_list, tmp);
    }
    return ;
}



void ft_is_token_word_for_heredoc(int *i, char *input_str, t_token_list *token_list)
{
    t_token_list *tmp;
    int j;
    int k;

    if (!ft_strchr(WHITESPACES, input_str[*i]))
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = WORD;
        j = *i;
        while(!ft_strchr(WHITESPACES, input_str[*i]) && input_str[*i] != '\0')
            *i = *i + 1;
        tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
        k = 0;
        while(!ft_strchr(WHITESPACES, input_str[j]))
        {
            tmp->value[k] = input_str[j];
            k++;
            j++;
        }
        tmp->value[k] = '\0';
        tmp->next = NULL;
        ft_list_add_back_for_token(&token_list, tmp);
    }
    return ;
}



void ft_parser_change_dollar_for_heredoc(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;
    char *tmp_string;

    if (list[0]->next == NULL)
        return ;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == WORD)
        {
            tmp_string = ft_change_dollar_sign_in_word(tmp->value, envp_list);
            free(tmp->value);
            tmp->value = tmp_string;
        }
        tmp = tmp->next;
    }
    tmp_string = NULL;
    return ;
}
