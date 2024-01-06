
#include "lib_for_minishell.h"

void ft_check_argc_quant(int argc)
{
    if (argc > 1)
    {
        printf(ERROR_ARGC_QUANT);
        exit(EXIT_FAILURE);
    }
    return ;
}
