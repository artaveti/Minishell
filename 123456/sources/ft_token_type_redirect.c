
#include "lib_for_minishell.h"

void ft_is_token_redir_int_heredoc(int *i, char *input_str, t_token_list *token_list)
{
    char redir_int;
    t_token_list *tmp;

    redir_int = '<';
    if (input_str[*i] == redir_int)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_INT;
        tmp->value = "<";
        tmp->next = NULL;
        *i = *i + 1;
        if (input_str[*i] == redir_int)
        {
            tmp->type = HEREDOC;
            tmp->value = "<<";
            *i = *i + 1;
        }
        ft_lstadd_back(&token_list, tmp);
    }
    return ;
}

void ft_is_token_redir_out_append(int *i, char *input_str, t_token_list *token_list)
{
    char redir_out;
    t_token_list *tmp;

    redir_out = '>';
    if (input_str[*i] == redir_out)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_OUT;
        tmp->value = ">";
        tmp->next = NULL;
        *i = *i + 1;
        if (input_str[*i] == redir_out)
        {
            tmp->type = REDIR_APPEND;
            tmp->value = ">>";
            *i = *i + 1;
        }
        ft_lstadd_back(&token_list, tmp);
    }
    return ;
}
