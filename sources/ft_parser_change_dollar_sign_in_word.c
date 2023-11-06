
#include "lib_for_minishell.h"

int  ft_char_find(char c, char const	*string);
char *ft_creat_first_part_of_word(char *string, char *symbols);
char **ft_creat_splitted_dollar(char *string);
void ft_creat_string_dollar_in_splitted(int i, char *string, char **splitted_dollar);
void ft_change_splitted_dollar(char ***splitted_dollar, t_environment_list **envp_list);
void ft_change_dollar_in_string_of_splitted(t_environment_list *tmp_env, char **string_from_splitted);
void ft_join_splitted_after_change(char **joined_str, char **first_part, char **splitted_dollar);
void ft_free_splitted_dollar(char ***splitted_dollar);
char *ft_strdup_quant(const char	*str, size_t quant);
int  ft_symbol_quant_in_string(char *string, char symbol);
char *ft_change_dollar_sign_in_string(char **string, char **name_and_value, int num_for_last, int *result);
void ft_creat_before_after_strings(int i, char **tmp_str, char **before_end_symb, char **after_end_symb);
char *ft_creat_last_part_of_word(char *string, char *symbols);
char *ft_change_dollar_sign_in_before_end_symb(char **before_end_symb, char **name_and_value, int num_for_last, int *result);
void ft_additional_for_else_if(char **str_for_dup, char **tmp_str, char **exit_status_str, int *result);


//////////////////////////////////////////////////////////////////////////////////////


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
    ft_free_splitted_dollar(&splitted_dollar);
    splitted_dollar = NULL;
    return (joined_str);
}



int	ft_char_find(char c, char const	*string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}



char *ft_creat_first_part_of_word(char *string, char *symbols)
{
    char *first_part;
    int i;

    i = 0;
    while (string[i] != '\0')
    {
        if (ft_strchr(symbols, string[i]))
        {
            first_part = ft_strdup_quant(string, i);
            return (first_part);
        }
        i++;
    }
    return (NULL);
}



char **ft_creat_splitted_dollar(char *string)
{
    char **splitted_dollar;
    int dollar_count;
    int i;

    dollar_count = ft_symbol_quant_in_string(string, '$');
    splitted_dollar = (char **)malloc(sizeof(char *) * (dollar_count + 1));
    i = 0;
    while(string[i] != '$' && string[i] != '\0')
        i++;
    ft_creat_string_dollar_in_splitted(i, string, splitted_dollar);
    return (splitted_dollar);
}



void ft_creat_string_dollar_in_splitted(int i, char *string, char **splitted_dollar)
{
    int j;
    int start;
    int char_quant;

    j = 0;
    while(string[i] != '\0')
    {
        if (string[i] == '$')
        {
            start = i;
            i++;
            char_quant = 1;
            while (string[i] != '$' && string[i] != '\0')
            {
                char_quant++;
                i++;
            }
            splitted_dollar[j] = ft_strdup_quant(&string[start], char_quant);
        }
        j++;
    }
    splitted_dollar[j] = NULL;
    return ;
}



void ft_change_splitted_dollar(char ***splitted_dollar, t_environment_list **envp_list)
{
    t_environment_list *tmp_env;
    char **tmp_splitted;
    int i;

    tmp_splitted = *splitted_dollar;
    i = 0;
    while(tmp_splitted[i] != NULL)
    {   
        tmp_env = *envp_list;
        ft_change_dollar_in_string_of_splitted(tmp_env, &tmp_splitted[i]);
        i++;
    }
    return ;
}



void ft_change_dollar_in_string_of_splitted(t_environment_list *tmp_env, char **string_from_splitted)
{
    char *tmp_str;
    int num_for_last;
    int result;

    num_for_last = 0;
    result = 0;
    while (tmp_env != NULL)
    {
        if (tmp_env->next == NULL)
            num_for_last = 1;
        tmp_str = ft_change_dollar_sign_in_string(string_from_splitted,
            tmp_env->name_and_value, num_for_last, &result);
        if (result == 1)
        {
            free(*string_from_splitted);
            *string_from_splitted = ft_strdup(tmp_str);
            free(tmp_str);
            break ;
        }
        tmp_env = tmp_env->next;
    }
    return ;
}



void ft_join_splitted_after_change(char **joined_str, char **first_part, char **splitted_dollar)
{
    char *tmp_joined_str;
    int i;

    *joined_str = ft_strjoin(*first_part, splitted_dollar[0]);
    i = 1;
    while (splitted_dollar[i] != NULL)
    {
        tmp_joined_str = *joined_str;
        *joined_str = ft_strjoin(*joined_str, splitted_dollar[i]);
        free(tmp_joined_str);
        i++;
    }
    return ;
}



void    ft_free_splitted_dollar(char ***splitted_dollar)
{
    int i;
    char **tmp_splitted;

    tmp_splitted = *splitted_dollar;
    i = 0;
    while (tmp_splitted[i] != NULL)
    {
        free(tmp_splitted[i]);
        tmp_splitted[i] = NULL;
        i++;
    }
    free(tmp_splitted[i]);
    tmp_splitted[i] = NULL;
    free(tmp_splitted);
    return ;
}



char	*ft_strdup_quant(const char	*str, size_t quant)
{
	char	*dup;
	size_t	i;

	dup = malloc(sizeof(char) * (quant + 1));
	if (!dup)
		return (0);
	i = 0;
	while (i < quant)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}



int ft_symbol_quant_in_string(char *string, char symbol)
{
    int i;
    int symbol_quant;

    i = symbol_quant = 0;
    while (string[i] != '\0')
    {
        if (string[i] == symbol)
            symbol_quant++;
        i++;
    }
    return (symbol_quant);
}



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



char *ft_change_dollar_sign_in_before_end_symb(char **before_end_symb, char **name_and_value, int num_for_last, int *result)
{
    char *tmp_str;
    char *str_for_dup;
    char *exit_status_str;

    tmp_str = *before_end_symb;
    *result = 0;
    if (tmp_str[1] == '\0')
    {
        tmp_str = ft_strdup("$");
        *result = 1;
    }
    else if (ft_strchr("?0123456789", tmp_str[1]) && tmp_str[1] != '\0')
        ft_additional_for_else_if(&str_for_dup, &tmp_str, &exit_status_str, result);
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



void ft_additional_for_else_if(char **str_for_dup, char **tmp_str, char **exit_status_str, int *result)
{
        *str_for_dup = ft_strdup(&tmp_str[0][2]);
        if (tmp_str[0][1] == '?')
        {
            *exit_status_str = ft_itoa(exit_status);
            *tmp_str = ft_strjoin(*exit_status_str, *str_for_dup);
            free(*exit_status_str);
        }
        else if (tmp_str[0][1] == '0')
            *tmp_str = ft_strjoin("minishell", *str_for_dup);
        else
            *tmp_str = ft_strdup(*str_for_dup);
        free(*str_for_dup);
        *result = 1;
        return ;
}



//char *ft_change_dollar_sign_in_word(char *string, t_environment_list *envp_list)
    // joined_str = ft_strjoin(first_part, splitted_dollar[0]);
    // i = 1;
    // while (splitted_dollar[i] != NULL)
    // {
    //     tmp_joined_str = joined_str;
    //     joined_str = ft_strjoin(joined_str, splitted_dollar[i]);
    //     free(tmp_joined_str);
    //     i++;
    // }


    
// void ft_change_splitted_dollar(char ***splitted_dollar, t_environment_list **envp_list)
// {
//     t_environment_list *tmp_env;
//     char **tmp_splitted;
//     char *tmp_str;
//     int num_for_last;
//     int result;
//     int i;

//     tmp_splitted = *splitted_dollar;
//     i = 0;
//     while(tmp_splitted[i] != NULL)
//     {   
//         tmp_env = *envp_list;
//         num_for_last = 0;
//         result = 0;
//         while (tmp_env != NULL)
//         {
//             if (tmp_env->next == NULL)
//                 num_for_last = 1;
//             tmp_str = ft_change_dollar_sign_in_string(&tmp_splitted[i], tmp_env->name_and_value, num_for_last, &result);
//             if (result == 1)
//             {
//                 free(tmp_splitted[i]);
//                 tmp_splitted[i] = ft_strdup(tmp_str);
//                 free(tmp_str);
//                 break ;
//             }
//             tmp_env = tmp_env->next;
//         }
//         i++;
//     }
//     return ;
// }



    // if(tmp_str[i] == '\0')
    // {
    //     before_end_symb = ft_strdup(tmp_str);
    //     after_end_symb = ft_strdup("");
    // }
    // else
    // {
    //     before_end_symb = ft_creat_first_part_of_word(tmp_str, END_OF_DOLLAR_SIGN);
    //     after_end_symb = ft_creat_last_part_of_word(tmp_str, END_OF_DOLLAR_SIGN);
    //     if (before_end_symb[1] == '\0' && after_end_symb[0] == '?')
    //     {
    //         free(before_end_symb);
    //         before_end_symb = ft_strdup("$?");
    //         tmp_str = after_end_symb;
    //         after_end_symb = ft_strdup(after_end_symb + 1);
    //         free(tmp_str);
    //     }
    // }



//         else if (ft_strchr("?0123456789", tmp_str[1]) && tmp_str[1] != '\0')
//     {

// void ft_additional_for_else_if(char **str_for_dup)
// {
//         str_for_dup = ft_strdup(&tmp_str[2]);
//         if (tmp_str[1] == '?')
//         {
//             exit_status_str = ft_itoa(exit_status);
//             tmp_str = ft_strjoin(exit_status_str, str_for_dup);
//             free(exit_status_str);
//         }
//         else if (tmp_str[1] == '0')
//             tmp_str = ft_strjoin("minishell", str_for_dup);
//         else
//             tmp_str = ft_strdup(str_for_dup);
//         free(str_for_dup);
//         *result = 1;
//         return ;
// }

//     }
