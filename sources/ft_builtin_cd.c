#include "lib_for_minishell.h"

//OLDPWD-n jnjel verakangneluc heto nakhord anunna stanum avtomat

t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) ;
void change_node_by_name(t_environment_list **envp, char *name, char *value);
int streq(char *s1, char *s2);

void ft_cd(t_environment_list **envp, char **array_of_strings, int fd_out, int exit_num) 
{
    dup2(fd_out, STDOUT_FILENO);
    (void)exit_num;
    printf("Hi cd\n");

    t_environment_list *home_node;
    int i;
    char *path;
    char *pwd;
    char *old_pwd;

    path = NULL;
    pwd = NULL;
    old_pwd = NULL;
    i = 1;
    if (array_of_strings[i] == NULL)
    {
        path = "HOME";
        home_node = find_node_by_name(*envp, path);
        if (home_node == NULL || home_node->name_and_value[1] == NULL)
        {
            printf("minishell: cd: HOME not set\n");
            return ;
        }
        else if (home_node->name_and_value[1][0] == '\0')
            return ;
        else
            path = ft_strdup(home_node->name_and_value[1]);
    }
    else
        path = ft_strdup(array_of_strings[i]);
    old_pwd = getcwd(NULL, 0);
    if (chdir(path) != 0)
    {
        printf("minishell: cd: %s: No such file or directory\n", path);
        free(path);
        free(old_pwd);
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
        return ;
    }
    pwd = getcwd(NULL, 0);
    change_node_by_name(envp,  "OLDPWD", old_pwd);
    change_node_by_name(envp,  "PWD", pwd);
    free(path);
    free(pwd);
    free(old_pwd);
    if (exit_num == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    g_exit_status_msh = EXIT_SUCCESS;
    return ;
}



t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) 
{
    while (envp != NULL)
     {
        if (envp->name_and_value != NULL && !ft_strncmp(envp->name_and_value[0], name, ft_strlen(name) + 1))
            return envp;
        envp = envp->next;
    }
    return NULL;
}



void change_node_by_name(t_environment_list **envp, char *name, char *value)
{
    t_environment_list *current = *envp;

    while (current != NULL) 
    {
        if (streq(current->name_and_value[0], name) != 0)
            {
                free(current->name_and_value[1]);
                current->name_and_value[1] = ft_strdup(value);
                if (current->envp_flag == 2)
                    return ;
                current->envp_flag = 1;
                return ;
            }
        current = current->next;
    }
    return ;
}



int streq(char *s1, char *s2)
{
    int i = 0;
    if ((!s1 || !(*s1) || !s2 || !(*s2)) || (ft_strlen(s1) != ft_strlen(s2)))
        return  0;
    while (s1[i])
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return 1;
}
