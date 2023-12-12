
// #include "lib_for_minishell.h"

// int    get_env(t_environment_list *envp);

// void    ft_pwd(char **str, t_environment_list **envp, int exit_num)
// {
//     (void)exit_num;
//     printf("Hi PWD\n");
//     char    *path_name;
//     (void)str;
 
//     path_name = getcwd(NULL, 0); 
//     if (!path_name) //ete chka
//     {
//         if (get_env(*envp) == 0) //error code 127? //cannot get env  u env path chka
//         {
//             perror("pwd"); //pwd error berum
//            // exit_status_msh =
//             return ;
//         }
//         return ;
//     }
//     else
//     {
//         printf("%s\n",  path_name); //tpuma path_name
//         free(path_name); //free anum
//         exit_status_msh = 0;
//         return ;
//     }
// }



// int    get_env(t_environment_list *envp) //mer env hamar getenv. veradarznuma pwd node value
// {
//     while (envp)
//     {
//         if (streq(envp->name_and_value[0], "PWD")) 
//         {
//             printf("%s\n", envp->name_and_value[1]);
//             return (1);
//         }
//         envp = envp->next;
//     }
//     return (0);
// }
