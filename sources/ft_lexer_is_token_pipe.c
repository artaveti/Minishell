
#include "lib_for_minishell.h"

void ft_is_token_pipe(int *i, char *input_str, t_token_list *token_list)
{
    char pipe;
    t_token_list *tmp;

    pipe = '|';
    if (input_str[*i] == pipe)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = PIPE;
        tmp->value = NULL;
        tmp->next = NULL;
        *i = *i + 1;
        ft_list_add_back_for_token(&token_list, tmp);
    }
    return ;
}
