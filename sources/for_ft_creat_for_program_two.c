
#include "lib_for_minishell.h"

void ft_creat_token_for_redir(t_token_list *redir_list, char *string, int type);
void ft_assign_word_to_argv(t_token_list *token_list, char ***argv_for_execve);
void ft_assign_string_to_word_of_argv(t_token_list *token_list, char ***argv_for_execve);

t_token_list *ft_creat_redir_list_for_execve(t_token_list *token_list)
{   
    t_token_list *redir_list;

    redir_list = (t_token_list *)malloc(sizeof(t_token_list));
    redir_list->type = START;
    redir_list->value = NULL;
    redir_list->next = NULL;
    while (token_list != NULL)
    {    
        if (token_list->type == REDIR_INT)
            ft_creat_token_for_redir(redir_list, token_list->value, REDIR_INT);
        else if (token_list->type == REDIR_OUT)
            ft_creat_token_for_redir(redir_list, token_list->value, REDIR_OUT);
        else if (token_list->type == HEREDOC)
            ft_creat_token_for_redir(redir_list, token_list->value, HEREDOC);
        else if (token_list->type == REDIR_APPEND)
            ft_creat_token_for_redir(redir_list, token_list->value, REDIR_APPEND);
        else if (token_list->type == PIPE)
            ft_creat_token_for_redir(redir_list, token_list->value, PIPE);
        token_list = token_list->next;
    }
    return (redir_list);
}



void ft_creat_token_for_redir(t_token_list *redir_list, char *string, int type)
{
    t_token_list *tmp;

    tmp = (t_token_list *)malloc(sizeof(t_token_list));
    if (type == PIPE)
        tmp->type = START;
    else
        tmp->type = type;
    if (string == NULL)
        tmp->value = NULL;
    else
        tmp->value = ft_strdup(string);
    tmp->next = NULL;
    ft_list_add_back_for_token(&redir_list, tmp);
    return ;
}



char ***ft_creat_argv_for_execve(t_token_list *token_list, int fd_quant)
{   
    char ***argv_for_execve;
    
    argv_for_execve = (char ***)malloc(sizeof(char **) * (fd_quant + 2));
    ft_assign_word_to_argv(token_list, argv_for_execve);
    ft_assign_string_to_word_of_argv(token_list, argv_for_execve);
    return (argv_for_execve);
}



void ft_assign_word_to_argv(t_token_list *token_list, char ***argv_for_execve)
{
    int i;
    int word_quant;

    i = 0;
    word_quant = 0;
    while(token_list != NULL)
    {
        if (token_list->type == WORD)
            word_quant++;
        if (token_list->type == PIPE || token_list->next == NULL)
        {
            argv_for_execve[i] = (char **)malloc(sizeof(char *) * (word_quant + 1));
            word_quant = 0;
            i++;
        }
        token_list = token_list->next;
    }
    return ;
}



void ft_assign_string_to_word_of_argv(t_token_list *token_list, char ***argv_for_execve)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (token_list != NULL)
    {
        if (token_list->type == WORD)
        {
            argv_for_execve[i][j] = ft_strdup(token_list->value);
            j++;
        }
        if (token_list->type == PIPE || token_list->next == NULL)
        {
            argv_for_execve[i][j] = NULL;
            j = 0;
            i++;
        }
        token_list = token_list->next;
    }
    argv_for_execve[i] = NULL;
    return ;
}
