
#include "lib_for_minishell.h"

int ft_env(char **str, t_environment_list *envp, int fd_out)
{
    if (str[1] != NULL)
    {
        dup2(fd_out, STDOUT_FILENO);
        printf(ERROR_ENV);
        exit(EXIT_ERROR_ARG);
    }
    while (envp != NULL)
    {
        if (envp->envp_flag == 1)
            printf("%s=%s\n", envp->name_and_value[0], envp->name_and_value[1]);
        envp = envp->next;
    }
    //exit(EXIT_SUCCESS);
    return (0);
}
