
#include "lib_for_minishell.h"

void ft_parser(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;
    char *tmp_string;

    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == WORD)
        {
            tmp_string = ft_change_dollar_sign_in_word(tmp->value, envp_list); ///malloced (char *tmp_string)
            free(tmp->value);
            tmp->value = tmp_string;
        }
        // else if (tmp->type == Q_DOUBLE)
        // ft_change_dollar_sign_in_q_double(&tmp->value, envp_list);
        tmp = tmp->next;
    }
    //tmp_string = NULL;
    //system("leaks minishell");
    return ;
}
