
#include "lib_for_minishell.h"

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
