#include "lib_for_minishell.h"

void    ft_pwd(t_environment_list **envp, char **str, int exit_num)
{
    (void)envp;
    (void)str;
    static char    *path_name;
    path_name = getcwd(NULL, 0);
    if (path_name == NULL)
    {
        printf(ERROR_PWD_CANT_ACCESS);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
            return ;
    }
    else
    {
        printf("%s\n",  path_name);
        free(path_name);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
        return ;
    }
}
