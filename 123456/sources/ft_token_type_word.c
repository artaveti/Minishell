
#include "lib_for_minishell.h"

void ft_is_token_word(int *i, char *input_str, t_token_list *token_list)
{
    char *not_word_chars;
    t_token_list *tmp;
    int j;
    int k;

    not_word_chars = " \t\r\n\v\'\"<>|";
    if (!ft_strchr(not_word_chars, input_str[*i]))
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = WORD;
        j = *i;
        while(!ft_strchr(not_word_chars, input_str[*i]) && input_str[*i] != '\0')
            *i = *i + 1;
        tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
        k = 0;
        while(!ft_strchr(not_word_chars, input_str[j]))
        {
            tmp->value[k] = input_str[j];
            k++;
            j++;
        }
        tmp->value[k] = '\0';
        tmp->next = NULL;
        ft_lstadd_back(&token_list, tmp);
    }
    return ;
}
