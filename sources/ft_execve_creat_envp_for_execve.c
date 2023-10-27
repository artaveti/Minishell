
#include "lib_for_minishell.h"

char    **ft_creat_envp_for_execve(t_environment_list *envp_list)
{
    char **envp_for_execve;
    char *tmp_str;
    int envp_len;
    int i;
    
    envp_len = ft_list_length_for_environment(envp_list);
    envp_for_execve = (char **)malloc(sizeof(char *) * (envp_len + 1));
    i = 0;
    while (envp_list != NULL)
    {
        envp_for_execve[i] = ft_strjoin(envp_list->name_and_value[0], "=");
        tmp_str = envp_for_execve[i];
        envp_for_execve[i] = ft_strjoin(envp_for_execve[i], envp_list->name_and_value[1]);
        free(tmp_str);
        envp_list = envp_list->next;
        i++;
    }
    envp_for_execve[i] = NULL;
    return (envp_for_execve);
}



// char    **ft_creat_envp_for_execve(t_environment_list *envp_list)
// {
//     t_environment_list *tmp_list;
//     char **envp_for_execve;
//     char *tmp_str;
//     int envp_len;
//     int i;
    
//     tmp_list = envp_list;
//     envp_len = ft_list_length_for_environment(tmp_list);
//     envp_for_execve = (char **)malloc(sizeof(char *) * (envp_len + 1));
//     i = 0;
//     while (tmp_list != NULL)
//     {
//         envp_for_execve[i] = ft_strjoin(tmp_list->name_and_value[0], "=");
//         tmp_str = envp_for_execve[i];
//         envp_for_execve[i] = ft_strjoin(envp_for_execve[i], tmp_list->name_and_value[1]);
//         free(tmp_str);
//         tmp_list = tmp_list->next;
//         i++;
//     }
//     envp_for_execve[i] = NULL;
//     return (envp_for_execve);
// }
