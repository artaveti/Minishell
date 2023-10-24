
#include "lib_for_minishell.h"

void ft_parser(t_token_list **list, t_environment_list *envp_list)
{
    ///////if null or string with only null not use like comand, if before tokens S_QUOTE or D_QUOTE sign $ sign $ must be deleted
    t_token_list *tmp;
    char *tmp_string;

    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == WORD)
        {
            tmp_string = ft_change_dollar_sign_in_word(tmp->value, envp_list);
            free(tmp->value);
            tmp->value = tmp_string;
        }
        else if (tmp->type == Q_DOUBLE)
        {
            tmp_string = ft_change_dollar_sign_in_q_double(&tmp->value, envp_list);
            free(tmp->value);
            tmp->value = tmp_string;
        }
        tmp = tmp->next;
    }
    tmp_string = NULL;
    //system("leaks minishell");
    return ;
}
