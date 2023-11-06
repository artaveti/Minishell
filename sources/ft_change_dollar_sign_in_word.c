
#include "lib_for_minishell.h"

char *ft_change_dollar_sign_in_word(char *string, t_environment_list *envp_list)
{
    char *joined_str;
    char *first_part;
    char **splitted_dollar;

    joined_str = NULL;
    if(!ft_char_find('$', string))
    {
        joined_str = ft_strdup(string);
        return (joined_str);
    }
    first_part = ft_creat_first_part_of_word(string, "$");
    splitted_dollar = ft_creat_splitted_dollar(string);
    ft_change_splitted_dollar(&splitted_dollar, &envp_list);
    ft_join_splitted_after_change(&joined_str, &first_part, splitted_dollar);
    free(first_part);
    ft_free_double_pointer_array(&splitted_dollar);
    splitted_dollar = NULL;
    return (joined_str);
}
