
#include "lib_for_minishell.h"

void ft_parser(t_token_list **list, t_environment_list *envp_list)
{
    if (list[0]->next == NULL)
        return ;
    ft_parser_first_change_dollar(list, envp_list);
    ft_parser_second_change_dollar(list, envp_list);
    ft_parser_third_change_quotes_to_word(list, envp_list);
    ft_parser_fourth_join_w(list, envp_list);
    ft_parser_remove_sep_from_list(list, envp_list);
    ft_parser_fifth_change_redir_value(list, envp_list);
    ft_parser_remove_sep_from_list(list, envp_list);
    return ;
}
