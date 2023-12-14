#include "lib_for_minishell.h"

int    get_env(t_environment_list *envp);

void    ft_pwd(t_environment_list **envp, char **str, int exit_num)
{
    (void)exit_num;
    printf("Hi PWD\n");
    char    *path_name;
    (void)str;
    (void)envp;
    path_name = getcwd(NULL, 0); 
    if (!path_name) //ete chka
    {
        if (getenv("PWD") == 0) //error code 127? //cannot get env  u env path chka
        {
            perror("pwd"); //pwd error berum
           // exit_status_msh =
            return ;
        }
        return ;
    }
    else
    {
        printf("%s\n",  path_name); //tpuma path_name
        free(path_name); //free anum
         exit_status_msh = 0;
        return ;
    }
}
