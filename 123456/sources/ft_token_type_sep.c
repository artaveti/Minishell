
#include "lib_for_minishell.h"

void ft_is_token_sep(int *i, char *input_str, t_token_list *token_list)
{
    char *whitespaces;
    t_token_list *tmp;

    whitespaces = " \t\r\n\v";
    if (ft_strchr(whitespaces, input_str[*i]))
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = SEP;
        tmp->value = NULL;
        tmp->next = NULL;
        while(input_str[*i] == ' ' || input_str[*i] == '\t'
            || input_str[*i] == '\r' || input_str[*i] == '\n'
            || input_str[*i] == '\v')
        *i = *i + 1;
        ft_lstadd_back(&token_list, tmp);
    }
    return ;
}
