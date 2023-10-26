
#include "lib_for_minishell.h"

int ft_count_spaces_for_joined_after_change(char *string);
int ft_count_chars_for_joined_after_change(char **splitted_str_q_double);
void    ft_creat_joined_after_change(char **joined_after_change, char *string, char **splitted_str_q_double);

//////////////////////////////////////////////////////////////////////////////////////



char    *ft_change_dollar_sign_in_q_double(char *string, t_environment_list *envp_list)
{
    char **splitted_str_q_double;
    char *joined_after_change;
    char *tmp_for_splitted;
    int i;
    int space_count;
    int char_count;

    splitted_str_q_double = ft_split(string, ' ');
    i = 0;
    // while(splitted_str_q_double[i] != NULL)
    // {
    //     printf("Before:I[%d]%s\n", i, splitted_str_q_double[i]);
    //     i++;
    // }
    i = 0;
    while(splitted_str_q_double[i] != NULL)
    {
        tmp_for_splitted = ft_change_dollar_sign_in_word(splitted_str_q_double[i], envp_list);
        free(splitted_str_q_double[i]);
        splitted_str_q_double[i] = tmp_for_splitted;
        i++;
    }
    tmp_for_splitted = NULL;
    //i = 0;
    // while(splitted_str_q_double[i] != NULL)
    // {
    //     printf("After:I[%d]%s\n", i, splitted_str_q_double[i]);
    //     i++;
    // }
    space_count = ft_count_spaces_for_joined_after_change(string);
    char_count = ft_count_chars_for_joined_after_change(splitted_str_q_double);
    //printf("SPACE_COUNT:::%d:::\n", space_count);
    //printf("CHAR_COUNT:::%d:::\n", char_count);
    joined_after_change = (char *)malloc(sizeof(char) * (space_count + char_count + 1));
    ft_creat_joined_after_change(&joined_after_change, string, splitted_str_q_double);
    //printf("joined_after_change:::%s:::\n", joined_after_change);
    i = 0;
    while (splitted_str_q_double[i] != NULL)
    {
        free(splitted_str_q_double[i]);
        i++;
    }
    free(splitted_str_q_double[i]);
    free(splitted_str_q_double);
    return (joined_after_change);
}



int ft_count_spaces_for_joined_after_change(char *string)
{
    int i;
    int space_count;

    i = 0;
    space_count = 0;
    while(string[i] != '\0')
    {
        if (string[i] == ' ')   //(ft_strchr(WHITESPACES, string[i]))  
            space_count++;
        i++;
    }
    return (space_count);
}



int ft_count_chars_for_joined_after_change(char **splitted_str_q_double)
{
    int i;
    int chars_count;

    i = 0;
    chars_count = 0;
    while(splitted_str_q_double[i] != NULL)
    {
        chars_count += ft_strlen(splitted_str_q_double[i]);
        i++;
    }
    return (chars_count);
}



void    ft_creat_joined_after_change(char **joined_after_change, char *string,
            char **splitted_str_q_double)
{
    int i;
    int j;
    int k;
    int l;

    i = 0;
    k = 0;
    j = 0;
    l = 0;
    while(string[i] != '\0')
    {
        while (string[i] == ' ')
        {
            joined_after_change[0][k] = ' ';
            k++;
            i++;
        }
        while(string[i] != ' ' && string[i] != '\0')
            i++;
        if (splitted_str_q_double[j] == NULL)
            break ;
        l = 0;
        while(splitted_str_q_double[j][l] != '\0')
        {
            joined_after_change[0][k] = splitted_str_q_double[j][l];
            k++;
            l++;
        }
        j++;
        if (string[i] == '\0')
            break ;
        }
    joined_after_change[0][k] = '\0';
    return ;
}









