
#include "lib_for_minishell.h"

void ft_free_double_pointer_array(char ***array)
{
    int i;
    char **tmp;

    tmp = *array;
    i = 0;
    while (tmp[i] != NULL)
    {
        free(tmp[i]);
        tmp[i] = NULL;
        i++;
    }
    free(*array);
    *array = NULL;
    return ;
}
