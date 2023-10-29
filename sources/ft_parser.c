
#include "lib_for_minishell.h"

/////// if null or string with only null not use like comand
/////// if before tokens S_QUOTE or D_QUOTE sign $ sign $ must be deleted
/////// ask about whitespaces
///////at first change $ sign and after join WORD, S_QUOTE, D_QUOTE

void ft_parser_first(t_token_list **list, t_environment_list *envp_list);
void ft_parser_second(t_token_list **list, t_environment_list *envp_list);
void ft_parser_third(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fourth(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fifth(t_token_list **list, t_environment_list *envp_list);
void ft_parser_sixth(t_token_list **list, t_environment_list *envp_list);
void ft_parser_seventh(t_token_list **list, t_environment_list *envp_list);
void ft_parser_eighth(t_token_list **list, t_environment_list *envp_list);
void ft_change_char_starting_from_the_last(char *string, char symbol);

//////////////////////////////////////////////////////////////////////////////////////


void ft_parser(t_token_list **list, t_environment_list *envp_list)
{
    ft_parser_first(list, envp_list);
    ft_parser_second(list, envp_list);
    ft_parser_third(list, envp_list);
    ft_parser_fourth(list, envp_list);
    ft_parser_fifth(list, envp_list);
    ft_parser_sixth(list, envp_list);
    ft_parser_seventh(list, envp_list);
    ft_parser_eighth(list, envp_list);
    return ;
}



void ft_parser_first(t_token_list **list, t_environment_list *envp_list)
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
            tmp_string = ft_change_dollar_sign_in_q_double(tmp->value, envp_list);
            free(tmp->value);
            tmp->value = tmp_string;
        }
        tmp = tmp->next;
    }
    tmp_string = NULL;
    //system("leaks minishell");
    return ;
}



void ft_parser_second(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == WORD && tmp->next != NULL
            && (tmp->next->type == Q_SINGLE || tmp->next->type == Q_DOUBLE))
                ft_change_char_starting_from_the_last(tmp->value, '$');
        tmp = tmp->next;
    }
    //system("leaks minishell");
    return ;
}



void ft_parser_third(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;
    char *tmp_string;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if ((tmp->type == WORD || tmp->type == Q_SINGLE || tmp->type == Q_DOUBLE) && tmp->next != NULL
            && (tmp->next->type == Q_SINGLE || tmp->next->type == Q_DOUBLE|| tmp->next->type == WORD))
        {
            tmp_string = tmp->next->value;
            tmp->next->value = ft_strjoin(tmp->value, tmp->next->value);
            tmp->next->type = WORD;
            free(tmp_string);
            tmp->type = SEP;
            free(tmp->value);
            tmp->value = NULL;
        }
        tmp = tmp->next;
    }
    //system("leaks minishell");
    return ;
}



void ft_parser_fourth(t_token_list **list, t_environment_list *envp_list)
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
    //system("leaks minishell");
    return ;
}



void ft_parser_fifth(t_token_list **list, t_environment_list *envp_list)
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
    //system("leaks minishell");
    return ;
}



void ft_parser_sixth(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == REDIR_INT || tmp->type == REDIR_OUT
            || tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
        {
            if (tmp->next == NULL)
            {
                printf(ERROR_SYNTAX, "newline");
                return ; //// must change exit_status = 1 and exit(exit_status);
            }
            else if (tmp->next->type != WORD)
            {
                printf(ERROR_SYNTAX, tmp->next->value);
                return ; //// must change exit_status = 1 and exit(exit_status);
            }
        }
        else if (tmp->type == PIPE)
        {
            if (tmp->next == NULL)
            {
                printf(ERROR_SYNTAX, "newline");
                return ; //// must change exit_status = 1 and exit(exit_status);
            }
            else if (tmp->next->type == PIPE)
            {
                printf(ERROR_SYNTAX, tmp->next->value);
                return ; //// must change exit_status = 1 and exit(exit_status);
            }
        }
        tmp = tmp->next;
    }
    return ;
}



void ft_parser_seventh(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *tmp;

    (void)envp_list;
    tmp = *list;
    while (tmp != NULL)
    {
        if (tmp->type == REDIR_INT || tmp->type == REDIR_OUT
            || tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
        {
            tmp->value = ft_strdup(tmp->next->value);
            free(tmp->next->value);
            tmp->next->value = NULL;
            tmp->next->type = WORD_REDIR;
        }
        tmp = tmp->next;
    }
    //system("leaks minishell");
    return ;
}



void ft_parser_eighth(t_token_list **list, t_environment_list *envp_list)
{
    t_token_list *previous;
    t_token_list *tmp;

    (void)envp_list;
    previous = *list;
    tmp = previous->next;
    while (tmp != NULL)
    {
        if (tmp->type == WORD_REDIR)
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
    //system("leaks minishell");
    return ;
}



void ft_change_char_starting_from_the_last(char *string, char symbol)
{
    size_t i;

    if (ft_strlen(string) == 0)
        return ;
    i = ft_strlen(string) - 1;
    while(i != 0)
    {
        if (string[i] == symbol)
            string[i] = '\0';
        else
            return ;
        i--;
    }
    if (string[i] == symbol)
        string[i] = '\0';
    return ;
}
