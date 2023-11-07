
#include "lib_for_minishell.h"

char *ft_change_dollar_sign_in_string(char **string, char **name_and_value, int num_for_last, int *result)
{
    char *tmp_str;
    char *before_end_symb;
    char *after_end_symb;
    int i;
    
    tmp_str = *string;
    before_end_symb = NULL;
    after_end_symb = NULL;
    i = 1;
    while (!(ft_strchr(END_OF_DOLLAR_SIGN, tmp_str[i])) && tmp_str[i] != '\0')
        i++;
    ft_creat_before_after_strings(i, &tmp_str, &before_end_symb,
        &after_end_symb);
    tmp_str = before_end_symb;
    before_end_symb = ft_change_dollar_sign_in_before_end_symb(&before_end_symb,
        name_and_value, num_for_last, result);
    if (*result == 1)
    {
        free(tmp_str);
            tmp_str = ft_strjoin(before_end_symb, after_end_symb);
    }
    free(before_end_symb);
    free(after_end_symb);
    return (tmp_str);
}



void ft_creat_before_after_strings(int i, char **tmp_str, char **before_end_symb, char **after_end_symb)
{
    if(tmp_str[0][i] == '\0')
    {
        *before_end_symb = ft_strdup(*tmp_str);
        *after_end_symb = ft_strdup("");
    }
    else
    {
        *before_end_symb = ft_creat_first_part_of_word(*tmp_str, END_OF_DOLLAR_SIGN);
        *after_end_symb = ft_creat_last_part_of_word(*tmp_str, END_OF_DOLLAR_SIGN);
        if (before_end_symb[0][1] == '\0' && after_end_symb[0][0] == '?')
        {
            free(*before_end_symb);
            *before_end_symb = ft_strdup("$?");
            *tmp_str = *after_end_symb;
            *after_end_symb = ft_strdup(*after_end_symb + 1);
            free(*tmp_str);
        }
    }
    return ;
}



char *ft_change_dollar_sign_in_before_end_symb(char **before_end_symb, char **name_and_value, int num_for_last, int *result)
{
    char *tmp_str;
    char *str_for_dup;
    char *exit_status_msh_str;

    tmp_str = *before_end_symb;
    *result = 0;
    if (tmp_str[1] == '\0')
    {
        tmp_str = ft_strdup("$");
        *result = 1;
    }
    else if (ft_strchr("?0123456789", tmp_str[1]) && tmp_str[1] != '\0')
        ft_additional_for_else_if(&str_for_dup, &tmp_str, &exit_status_msh_str, result);
    else if (!ft_memcmp(&tmp_str[1], name_and_value[0], ft_strlen(&tmp_str[1]) + 1))
    {
        tmp_str = ft_strdup(name_and_value[1]);
        *result = 1;
    }
    else if (num_for_last == 1)
    {
        tmp_str = ft_strdup("");
        *result = 1;
    }
    return (tmp_str);
}



char *ft_creat_last_part_of_word(char *string, char *symbols)
{
    char *last_part;
    int string_len;
    int i;

    i = 0;
    while (string[i] != '\0')
    {
        if (ft_strchr(symbols, string[i]))
        {
            string_len = ft_strlen(string);
            last_part = ft_strdup_quant(&string[i], string_len - i);
            return (last_part);
        }
        i++;
    }
    return (NULL);
}



void ft_additional_for_else_if(char **str_for_dup, char **tmp_str, char **exit_status_msh_str, int *result)
{
        *str_for_dup = ft_strdup(&tmp_str[0][2]);
        if (tmp_str[0][1] == '?')
        {
            *exit_status_msh_str = ft_itoa(exit_status_msh);
            *tmp_str = ft_strjoin(*exit_status_msh_str, *str_for_dup);
            free(*exit_status_msh_str);
        }
        else if (tmp_str[0][1] == '0')
            *tmp_str = ft_strjoin("minishell", *str_for_dup);
        else
            *tmp_str = ft_strdup(*str_for_dup);
        free(*str_for_dup);
        *result = 1;
        return ;
}
