
#include "lib_for_minishell.h"

void ft_change_dollar_in_splitted_qdoub(char ***splitted_str, t_environment_list *envp_list);
int  ft_count_spaces_for_joined_after_change(char *string);
int  ft_count_chars_for_joined_after_change(char **splitted_str);
char *ft_creat_joined_after_change(char *string, char **splitted_str, int quant);
void ft_additional_for_creat_joined_first(int *i, int *k, char *string, char *joined_after_change);
void ft_additional_for_creat_joined_second(int *j, int *k, char **splitted_str, char *joined_after_change);

//////////////////////////////////////////////////////////////////////////////////////


char    *ft_change_dollar_sign_in_qdoub(char *string, t_environment_list *envp_list)
{
    char **splitted_str;
    char *joined_after_change;
    int space_quant;
    int char_quant;

    splitted_str = ft_split(string, ' ');
    ft_change_dollar_in_splitted_qdoub(&splitted_str, envp_list);
    space_quant = ft_count_spaces_for_joined_after_change(string);
    char_quant = ft_count_chars_for_joined_after_change(splitted_str);
    joined_after_change = ft_creat_joined_after_change(string, splitted_str,
        space_quant + char_quant);
    ft_free_double_pointer_array(&splitted_str);
    return (joined_after_change);
}



void ft_change_dollar_in_splitted_qdoub(char ***splitted_str, t_environment_list *envp_list)
{
    int i;
    char *tmp_for_splitted;
    char **tmp_splitted_str;

    tmp_splitted_str = *splitted_str;
    i = 0;
    while(tmp_splitted_str[i] != NULL)
    {
        tmp_for_splitted = ft_change_dollar_sign_in_word(tmp_splitted_str[i], envp_list);
        free(tmp_splitted_str[i]);
        tmp_splitted_str[i] = tmp_for_splitted;
        i++;
    }
    tmp_for_splitted = NULL;
    return ;
}



int ft_count_spaces_for_joined_after_change(char *string)
{
    int i;
    int space_count;

    i = 0;
    space_count = 0;
    while(string[i] != '\0')
    {
        if (string[i] == ' ')   //if(ft_strchr(WHITESPACES, string[i]))
            space_count++;
        i++;
    }
    return (space_count);
}



int ft_count_chars_for_joined_after_change(char **splitted_str)
{
    int i;
    int chars_count;

    i = 0;
    chars_count = 0;
    while(splitted_str[i] != NULL)
    {
        chars_count += ft_strlen(splitted_str[i]);
        i++;
    }
    return (chars_count);
}



char    *ft_creat_joined_after_change(char *string, char **splitted_str, int quant)
{
    char *joined_after_change;
    int i;
    int j;
    int k;

    joined_after_change = (char *)malloc(sizeof(char) * (quant + 1));
    i = 0;
    j = 0;
    k = 0;
    while(string[i] != '\0')
    {
        ft_additional_for_creat_joined_first(&i, &k, string,
            joined_after_change);
        if (splitted_str[j] == NULL)
            break ;
        ft_additional_for_creat_joined_second(&j, &k, splitted_str,
            joined_after_change);
        if (string[i] == '\0')
            break ;
    }
    joined_after_change[k] = '\0';
    return (joined_after_change);
}



void ft_additional_for_creat_joined_first(int *i, int *k, char *string, char *joined_after_change)
{
    while (string[*i] == ' ')
    {
        joined_after_change[*k] = ' ';
        *k = *k + 1;
        *i = *i + 1;
    }
    while(string[*i] != ' ' && string[*i] != '\0')
        *i = *i + 1;
    return ;
}



void ft_additional_for_creat_joined_second(int *j, int *k, char **splitted_str, char *joined_after_change)
{
    int l;

    l = 0;
    while(splitted_str[*j][l] != '\0')
    {
        joined_after_change[*k] = splitted_str[*j][l];
        *k = *k + 1;
        l++;
    }
    *j = *j + 1;
    return ;
}
