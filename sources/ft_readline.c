
#include "lib_for_minishell.h"

char *ft_readline(void)
{
    char *str;
    int i;

    str = readline("minishell>");
    i = 0;
    if (str == NULL)
        return(NULL);
    while(str[i] != '\0')
    {
        if(ft_strchr(WHITESPACES_RL, str[i]))
            i++;
        else
            break;
    }
    if (str[i] != '\0')
        add_history(str);
    return (str);
}
