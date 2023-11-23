
#include "lib_for_minishell.h"

void ft_free_double_pointer_array(char ***array)
{
    int i;
    char **tmp;

    if (!*array || *array == NULL)
        return ;
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



void ft_free_double_pointer_int(int ***array, int fd_quant_pipe)
{
    int i;
    int **tmp;

    tmp = *array;
    i = 0;
    while (i < fd_quant_pipe)
    {
        free(tmp[i]);
        tmp[i] = NULL;
        i++;
    }
    free(*array);
    *array = NULL;
    return ;
}



void ft_free_triple_pointer_array(char ****array)
{
    int i;
    char ***tmp;

    tmp = *array;
    i = 0;
    while (tmp[i] != NULL)
    {
        ft_free_double_pointer_array(&tmp[i]);
        i++;
    }
    free(*array);
    *array = NULL;
    return ;
}
