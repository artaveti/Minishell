
#include "lib_for_minishell.h"

void ft_parser_for_heredoc(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fourth_join_w_for_heredoc(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fifth_change_redir_value_for_heredoc(t_token_list **list, t_environment_list *envp_list);
void ft_parser_remove_all_except_heredoc(t_token_list **list, t_environment_list *envp_list);

void    ft_creat_token_for_heredoc(char *input_str, t_token_list *heredoc_list, t_environment_list *envp_list)
{
    ft_lexer(input_str, heredoc_list);
    ft_parser_for_heredoc(&heredoc_list, envp_list);
    
    return ;
}



void ft_parser_for_heredoc(t_token_list **heredoc_list, t_environment_list *envp_list)
{
    if (heredoc_list[0]->next == NULL)
        return ;
    ft_parser_second_change_dollar(heredoc_list, envp_list);
    ft_parser_fourth_join_w_for_heredoc(heredoc_list, envp_list);
    ft_parser_remove_sep_from_list(heredoc_list, envp_list);
    ft_parser_fifth_change_redir_value_for_heredoc(heredoc_list, envp_list);
    ft_parser_remove_all_except_heredoc(heredoc_list, envp_list);
    return ;
}


void ft_parser_fourth_join_w_for_heredoc(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;
    char *tmp_string;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if ((tmp->type == WORD || tmp->type == Q_SINGLE || tmp->type == Q_DOUBLE)
            && tmp->next != NULL
            && (tmp->next->type == WORD || tmp->next->type == Q_SINGLE || tmp->next->type == Q_DOUBLE))
        {
            tmp_string = tmp->next->value;
            tmp->next->type = Q_DOUBLE;
            tmp->next->value = ft_strjoin(tmp->value, tmp->next->value);
            free(tmp_string);
            tmp->type = SEP;
            free(tmp->value);
            tmp->value = NULL;
        }
        tmp = tmp->next;
    }
    return ;
}



void ft_parser_fifth_change_redir_value_for_heredoc(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == HEREDOC
            && tmp->next != NULL
            && (tmp->next->type == WORD || tmp->next->type == Q_SINGLE || tmp->next->type == Q_DOUBLE))
        {
            tmp->value = ft_strdup(tmp->next->value);
            if (tmp->next->type == WORD)
                tmp->next->type = HEREDOC_W;
            else if (tmp->next->type == Q_SINGLE)
                tmp->next->type = HEREDOC_Q_S;
            else if (tmp->next->type == Q_DOUBLE)
                tmp->next->type = HEREDOC_Q_D;
            // free(tmp->next->value);
            // tmp->next->value = NULL;
        }
        tmp = tmp->next;
    }
    return ;
}



void ft_parser_remove_all_except_heredoc(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *previous;
    t_token_list *tmp;

    (void)envp_list;
    previous = *list;
    tmp = previous->next;
    while (tmp != NULL)
    {
        if (tmp->type != HEREDOC && tmp->type != HEREDOC_W
            && tmp->type != HEREDOC_Q_S && tmp->type != HEREDOC_Q_D)
        {
            previous->next = tmp->next;
            free(tmp->value);
            tmp->value = NULL;
            free(tmp);
            tmp = previous->next;
        }
        else
        {
            previous = previous->next;
            tmp = previous->next;
        }
    }
    return ;
}
