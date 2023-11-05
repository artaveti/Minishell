
#include "lib_for_minishell.h"

void ft_parser_first_change_dollar(t_token_list **list, t_environment_list *envp_list);
void ft_parser_second_change_dollar(t_token_list **list, t_environment_list *envp_list);
void ft_parser_third(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fourth(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fifth(t_token_list **list, t_environment_list *envp_list);
void ft_parser_remove_sep_from_list(t_token_list **list, t_environment_list *envp_list);
char *ft_change_char_from_the_last(char *string, char symbol);


//////////////////////////////////////////////////////////////////////////////////////


void ft_parser(t_token_list **list, t_environment_list *envp_list)
{
    ft_parser_first_change_dollar(list, envp_list);
    ft_parser_second_change_dollar(list, envp_list);
    ft_parser_third(list, envp_list);
    ft_parser_fourth(list, envp_list);
    ft_parser_remove_sep_from_list(list, envp_list);
    ft_parser_fifth(list, envp_list);
    ft_parser_remove_sep_from_list(list, envp_list);
    return ;
}



void ft_parser_first_change_dollar(t_token_list **list, t_environment_list *envp_list)
{
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
            tmp_string = ft_change_dollar_sign_in_qdoub(tmp->value, envp_list);
            free(tmp->value);
            tmp->value = tmp_string;
        }
        tmp = tmp->next;
    }
    tmp_string = NULL;
    return ;
}



void ft_parser_second_change_dollar(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;
    char *tmp_string;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == WORD && tmp->next != NULL
            && (tmp->next->type == Q_SINGLE || tmp->next->type == Q_DOUBLE))
            {
                tmp_string = ft_change_char_from_the_last(tmp->value, '$');
                free(tmp->value);
                tmp->value = tmp_string;
            }
        tmp = tmp->next;
    }
    tmp_string = NULL;
    return ;
}



void ft_parser_third(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == Q_SINGLE || tmp->type == Q_DOUBLE)
            tmp->type = WORD;
        tmp = tmp->next;
    }
    return ;
}



void ft_parser_fourth(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;
    char *tmp_string;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == WORD && tmp->next != NULL && tmp->next->type == WORD)
        {
            tmp_string = tmp->next->value;
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



void ft_parser_fifth(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if ((tmp->type == REDIR_INT || tmp->type == REDIR_OUT
            || tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
            && tmp->next != NULL && tmp->next->type == WORD)
        {
            tmp->value = ft_strdup(tmp->next->value);
            free(tmp->next->value);
            tmp->next->value = NULL;
            tmp->next->type = SEP;
        }
        tmp = tmp->next;
    }
    return ;
}



void ft_parser_remove_sep_from_list(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *previous;
    t_token_list *tmp;

    (void)envp_list;
    previous = *list;
    tmp = previous->next;
    while (tmp != NULL)
    {
        if (tmp->type == SEP)
        {
            previous->next = tmp->next;
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



char *ft_change_char_from_the_last(char *string, char symbol)
{
    size_t i;
    char *tmp_string;

    if (ft_strlen(string) == 0)
    {
        tmp_string = ft_strdup("");
        return (tmp_string);
    }
    i = ft_strlen(string) - 1;
    while(i != 0)
    {
        if (string[i] == symbol)
            string[i] = '\0';
        else
            break ;
        i--;
    }
    if (string[i] == symbol)
        string[i] = '\0';
    tmp_string = ft_strdup(string);
    return (tmp_string);
}
