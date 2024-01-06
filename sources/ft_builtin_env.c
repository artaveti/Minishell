
#include "lib_for_minishell.h"

void ft_env(t_environment_list **envp, t_for_prog *prog, char **array_of_strings, int fd_out)
{
    t_environment_list *tmp;
    tmp = *envp;

    if (array_of_strings[1] != NULL)
    {
        dup2(fd_out, STDOUT_FILENO);
        printf(ERROR_ENV);
        if (prog->check_builtin == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
        return ;
    }
    while (tmp != NULL)
    {
        if (tmp->envp_flag == 1)
            printf("%s=%s\n", tmp->name_and_value[0], tmp->name_and_value[1]);
        tmp = tmp->next;
    }
    if (prog->check_builtin == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    g_exit_status_msh = EXIT_SUCCESS;
    return ;
}
