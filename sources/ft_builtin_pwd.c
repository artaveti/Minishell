#include "lib_for_minishell.h"

int    get_env(t_environment_list *envp);

void    ft_pwd(t_environment_list **envp, char **str, int exit_num)
{
    (void)exit_num;
    char    *path_name;
    (void)str;
    (void)envp;
    path_name = getcwd(NULL, 0); 
    if (!path_name)
    {
        if (getenv("PWD") == 0) //error code 127? //cannot get env  u env path chka
        {
            perror("pwd"); //pwd error berum
            if (exit_num == BUILTIN_EXIT)
                exit(EXIT_FAILURE);
            g_exit_status_msh = EXIT_FAILURE;
            return ;
        }
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
