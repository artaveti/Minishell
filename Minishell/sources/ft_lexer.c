
#include "lib_for_minishell.h"

void ft_lexer(char *input_str, t_token_list *token_list)
{
    int i;

    i = 0;
    while (input_str[i] != '\0')
    {
        ft_is_token_sep(&i, input_str, token_list);
        ft_is_token_single_quote(&i, input_str, token_list);
        ft_is_token_double_quote(&i, input_str, token_list);
        ft_is_token_redir_int_heredoc(&i, input_str, token_list);
        ft_is_token_redir_out_append(&i, input_str, token_list);
        ft_is_token_pipe(&i, input_str, token_list);
        ft_is_token_word(&i, input_str, token_list);
    }
    return ;
}
