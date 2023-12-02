
#include "lib_for_minishell.h"

void ft_heredoc_quant_error(t_token_list **list, int *error_num)
{
    t_token_list *tmp;
    int quant;

    if (*error_num > 0)
        return ;
    tmp = *list;
    quant = 0;
    while (tmp != NULL)
    {
        if (tmp->type == HEREDOC)
            quant++;
        if (quant > 16)
        {
            *error_num = 2;
            printf(ERROR_HEREDOC_QUANT);
            exit(EXIT_ERROR_HEREDOC_QUANT);
        }
        tmp = tmp->next;
    }
    return ;
}
