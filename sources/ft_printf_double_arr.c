
#include "lib_for_minishell.h"

void ft_printf_double_arr(char **double_arr)
{
    int i;
    
    i = 0;
    while(double_arr[i] != NULL)
    {
        printf("I[%d](%s)\n", i, double_arr[i]);
        i++;
    }
    return ;
}
