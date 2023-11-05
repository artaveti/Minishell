
#include "lib_for_minishell.h"

void    ft_list_free_for_token(t_token_list **list)
{
    t_token_list *tmp;
    t_token_list *next;
    int i;

    i = 0;
    tmp = *list;
    while(tmp != NULL)
    {
        next = tmp->next;
        if (tmp->type == WORD || tmp->type == REDIR_INT || tmp->type == REDIR_OUT
            || tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
                free(tmp->value);
        free(tmp);
        tmp = next;
    }
    *list = NULL;
    return ;
}
