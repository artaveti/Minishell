
#include "lib_for_minishell.h"

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
