
#include "lib_for_minishell.h"

t_token_list *ft_list_creat_token(void)
{
    t_token_list *start;

    start = malloc(sizeof(t_token_list));
    start->type = START;
    start->value = NULL;
    start->next = NULL;
    return (start);
}
