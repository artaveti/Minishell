
#include "lib_for_minishell.h"

int ft_syntax_error_first_token(t_token_list **list);
int ft_syntax_error_redirect_pipe(t_token_list **list);


//////////////////////////////////////////////////////////////////////////////////////


int ft_syntax_error(t_token_list **list)
{
    int error_num;

    error_num = 0;
    if (*list == NULL)
        return (error_num);
    error_num = ft_syntax_error_first_token(list);
    if (error_num > 0)
        return (error_num);
    error_num = ft_syntax_error_redirect_pipe(list);
    if (error_num > 0)
        return (error_num);
    return (error_num);
}



int ft_syntax_error_first_token(t_token_list **list)
{
    t_token_list *tmp;

    tmp = *list;
    if (tmp->type != WORD && tmp->type != REDIR_INT && tmp->type != REDIR_OUT
                && tmp->type != REDIR_APPEND && tmp->type != HEREDOC)
    {
        if (tmp->type == PIPE)
            printf(ERROR_SYNTAX, "|");
        return (EXIT_ERROR_SYNTAX);
    }
    return (0);
}


int ft_syntax_error_redirect_pipe(t_token_list **list)
{
    t_token_list *tmp;

    tmp = *list;
    while (tmp != NULL)
    {
        if ((tmp->type == REDIR_INT || tmp->type == REDIR_OUT
            || tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
            && tmp->value == NULL)
        {
            if (tmp->next == NULL)
                printf(ERROR_SYNTAX, "newline");
            else if (tmp->next->type == REDIR_INT)
                printf(ERROR_SYNTAX, "<");
            else if (tmp->next->type == REDIR_OUT)
                printf(ERROR_SYNTAX, ">");
            else if (tmp->next->type == REDIR_APPEND)
                printf(ERROR_SYNTAX, ">>");
            else if (tmp->next->type == HEREDOC)
                printf(ERROR_SYNTAX, "<<");
            else if (tmp->next->type == PIPE)
                printf(ERROR_SYNTAX, "|");
            return (EXIT_ERROR_SYNTAX);
        }
        else if (tmp->type == PIPE)
        {
            if (tmp->next == NULL)
            {
                printf(ERROR_SYNTAX, "newline");
                return (EXIT_ERROR_SYNTAX);
            }
            else if (tmp->next->type == PIPE)
            {
                printf(ERROR_SYNTAX, "|");
                return (EXIT_ERROR_SYNTAX);
            }
        }
    tmp = tmp->next;
    }
    return (0);
}


