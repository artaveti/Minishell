#include "lib_for_minishell.h"

//OLDPWD-n jnjel verakangneluc heto nakhord anunna stanum avtomat

t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) ;
void change_node_by_name(t_environment_list **envp, char *name, char *value);
int streq(char *s1, char *s2);

void ft_cd(t_environment_list **envp, t_for_prog *prog, char **array_of_strings, int fd_out)
{
    t_environment_list *tmp_node;
    t_environment_list *pwd_of_list;
    int i;
    char *path;
    char *pwd;

    path = NULL;
    pwd = NULL;
    i = 1;
    if (array_of_strings[i] == NULL)
    {
        tmp_node = find_node_by_name(*envp, "HOME");
        if (tmp_node == NULL || tmp_node->name_and_value[1] == NULL)
        {
            dup2(fd_out, STDOUT_FILENO);
            printf("minishell: cd: HOME not set\n");
            if (prog->check_builtin == BUILTIN_EXIT) 
                exit(EXIT_FAILURE);
            g_exit_status_msh = EXIT_FAILURE;
            return ;
        }
        else if (tmp_node->name_and_value[1][0] == '\0')
        {
            if (prog->pwd_str[0] == NULL)
            {
                printf(ERROR_CD_GETCWD_CANT_ACCESS);
            }
            if (prog->check_builtin == BUILTIN_EXIT)
                exit(EXIT_SUCCESS);
            g_exit_status_msh = EXIT_SUCCESS;
            return ;
        }
        else
            path = ft_strdup(tmp_node->name_and_value[1]);
    }
    else
        path = ft_strdup(array_of_strings[i]);
    if ((prog->pwd_str[0] == NULL && !ft_strncmp(path, "..", 3)) || chdir(path) != 0)
    {
        if (prog->pwd_str[0] == NULL)
        {
            printf(ERROR_CD_GETCWD_CANT_ACCESS);
        }
        printf("minishell: cd: %s: No such file or directory\n", path);
        free(path);
        if (prog->check_builtin == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
        return ;
    }
    if (prog->pwd_str[0] == NULL)
    {
        printf(ERROR_CD_GETCWD_CANT_ACCESS);
    }
    // .; ..; /;
    pwd = getcwd(NULL, 0);
    //printf("pwd(before):(%s)\n", prog->pwd_str[0]);
    free(prog->pwd_str[0]);
    if (pwd == NULL)
    {
        prog->pwd_str[0] = ft_strdup(".");
    }
    else
    {
        prog->pwd_str[0] = ft_strdup(pwd);
    }
    //printf("pwd(after):(%s)\n", pwd);
    tmp_node = find_node_by_name(*envp, "PWD");
    if (tmp_node == NULL || tmp_node->name_and_value[1] == NULL)
    {
        change_node_by_name(envp,  "OLDPWD", "");
    }
    else
    {
        change_node_by_name(envp,  "OLDPWD", tmp_node->name_and_value[1]);
    }
    if (tmp_node == NULL)
    {
        pwd_of_list = (t_environment_list *)malloc(sizeof(t_environment_list));
        pwd_of_list->name_and_value = (char **)malloc(sizeof(char *) * 3);
        pwd_of_list->envp_flag = 1;
        pwd_of_list->name_and_value[0] = ft_strdup("PWD");
        pwd_of_list->name_and_value[1] = NULL;
        pwd_of_list->name_and_value[2] = NULL;
        pwd_of_list->next = NULL;
        ft_list_add_back_for_environment(envp, pwd_of_list);
    }
    change_node_by_name(envp,  "PWD", prog->pwd_str[0]);
    free(path);
    free(pwd);
    if (prog->check_builtin == BUILTIN_EXIT)
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
