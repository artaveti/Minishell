#include "lib_for_minishell.h"

int ft_pwd(t_environment_list **envp, char **array_of_strings, int check_num, int exit_num)
{
    (void)envp;
    (void)array_of_strings;

    char    *path_name;
    path_name = getcwd(NULL, 0);
    if (check_num == FIRST_CHECK_PWD)
    {
        if (path_name == NULL)
        {
            printf(ERROR_PWD_CANT_ACCESS_FIRST_CHECK);
            return (EXIT_FAILURE);
        }
        else
            return (EXIT_SUCCESS);
    }
    if (path_name == NULL)
    {
        printf(ERROR_PWD_CANT_ACCESS_SECOND_CHECK);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
            return (EXIT_FAILURE);
    }
    else
    {
        printf("%s\n",  path_name);
        free(path_name);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_SUCCESS);
        g_exit_status_msh = EXIT_SUCCESS;
        return (EXIT_SUCCESS);
    }
}
