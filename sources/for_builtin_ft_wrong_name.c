
#include "lib_for_minishell.h"

int ft_wrong_name(char *name, char *command)
{
    int len;
    int i;

    if (!(name[0] == '_' ||  ft_isalpha(name[0])) || !name || !(*name))
    {
        printf(ERROR_WRONG_NAME, command, name);
        return (1);
    }
    len = ft_strlen(name);
    i = 0;
    while (i < len)
    {
        if (!(ft_isalnum(name[i]) || name[i] == '_')) 
        {
            printf(ERROR_WRONG_NAME, command, name);
            return (1);
        }
        i++;
    }
    return (0);
}
