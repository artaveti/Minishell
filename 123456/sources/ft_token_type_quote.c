
#include "lib_for_minishell.h"

void ft_is_token_single_quote(int *i, char *input_str, t_token_list *token_list)
{
    char single_quote;
    t_token_list *tmp;
    int j;
    int k;

    single_quote = '\'';
    if (input_str[*i] == single_quote)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = Q_SINGLE;
        *i = *i + 1;
        j = *i;
        while(input_str[*i] != single_quote && input_str[*i] != '\0')
            *i = *i + 1;
        tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
        k = 0;
        while(input_str[j] != single_quote && input_str[j] != '\0')
        {
            tmp->value[k] = input_str[j];
            k++;
            j++;
        }
        tmp->value[k] = '\0';
        tmp->next = NULL;
        if(input_str[*i] == single_quote)
            *i = *i + 1;
        ft_lstadd_back(&token_list, tmp);
    }
    return ;
}

void ft_is_token_double_quote(int *i, char *input_str, t_token_list *token_list)
{
    char double_quote;
    t_token_list *tmp;
    int j;
    int k;

    double_quote = '\"';
    if (input_str[*i] == double_quote)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = Q_DOUBLE;
        *i = *i + 1;
        j = *i;
        while(input_str[*i] != double_quote && input_str[*i] != '\0')
            *i = *i + 1;
        tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
        k = 0;
        while(input_str[j] != double_quote && input_str[j] != '\0')
        {
            tmp->value[k] = input_str[j];
            k++;
            j++;
        }
        tmp->value[k] = '\0';
        tmp->next = NULL;
        if(input_str[*i] == double_quote)
            *i = *i + 1;
        ft_lstadd_back(&token_list, tmp);
    }
    return ;
}
