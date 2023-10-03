
#include "lib_for_minishell.h"

int ft_count_envp_len(char *envp[])
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    return (i);
}
