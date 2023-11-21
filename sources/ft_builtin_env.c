
#include "lib_for_minishell.h"

int ft_env(char **str, t_environment_list *envp, int fd_out, int exit_num)
{
    if (str[1] != NULL)
    {
        dup2(fd_out, STDOUT_FILENO);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_ERROR_ARG);
        else
        {
            exit_status_msh = EXIT_ERROR_ENV;
            return (BUILTIN_RETURN);
        }
        printf("=======================\n");
    }
    while (envp != NULL)
    {
        if (envp->envp_flag == 1)
            printf("%s=%s\n", envp->name_and_value[0], envp->name_and_value[1]);
        envp = envp->next;
    }
    if (exit_num == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    else
        return (BUILTIN_RETURN);
}
